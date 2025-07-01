#include "ResourceManager.h"
#include "RenderSystem.h"
#include "Texture2D.h"

/// ResourceManager Init
HRESULT ResourceManager::Init()
{
    HRESULT hr;

    // WIC Imaging Factory ����
    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(wicImagingFactory.GetAddressOf())
    );
    if (FAILED(hr))
        return hr;

    // RenderSystem���� D3D11Device ��������
    ComPtr<ID3D11Device> d3dDevice = RenderSystem::Get().d3dDevice;
    if (!d3dDevice)
        return E_FAIL;

    // IDXGIDevice �������̽� ���
    ComPtr<IDXGIDevice> dxgiDeviceBase;
    hr = d3dDevice->QueryInterface(dxgiDeviceBase.GetAddressOf());
    if (FAILED(hr))
        return hr;

    // IDXGIDeviceBase -> IDXGIDevice3 ��ȯ
    hr = dxgiDeviceBase.As(&dxgiDevice);
    if (FAILED(hr))
        return hr;

    // IDXGIAdapter ���
    ComPtr<IDXGIAdapter> dxgiAdapterBase;
    hr = dxgiDevice->GetAdapter(dxgiAdapterBase.GetAddressOf());
    if (FAILED(hr))
        return hr;

    // IDXGIAdapter -> IDXGIAdapter3 ��ȯ
    hr = dxgiAdapterBase.As(&dxgiAdapter);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

/// Format bytes to human-readable string
string ResourceManager::FormatBytes(UINT64 bytes) {
    constexpr double KB = 1024.0;
    constexpr double MB = KB * 1024.0;
    constexpr double GB = MB * 1024.0;

    ostringstream oss;
    oss << fixed << setprecision(2);

    if (bytes >= static_cast<UINT64>(GB))
        oss << (bytes / GB) << " GB";
    else if (bytes >= static_cast<UINT64>(MB))
        oss << (bytes / MB) << " MB";
    else if (bytes >= static_cast<UINT64>(KB))
        oss << (bytes / KB) << " KB";
    else
        oss << bytes << " B";

    return oss.str();
}

/// Print memory usage
void ResourceManager::PrintMemoryUsage() {
    DXGI_QUERY_VIDEO_MEMORY_INFO memInfo = {};
    HANDLE hProcess = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS_EX pmc;
    pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);
    HRESULT hr = dxgiAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &memInfo);
    if (GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        string vramStr = "VRAM: " + FormatBytes(memInfo.CurrentUsage) + "\n";
        string dramStr = "DRAM: " + FormatBytes(pmc.WorkingSetSize) + "\n";
        string pageFileStr = "PageFile: " + FormatBytes(pmc.PagefileUsage - pmc.WorkingSetSize) + "\n";

		OutputDebugStringA("---------�޸� ��ȸ---------\n");
        OutputDebugStringA(vramStr.c_str());
        OutputDebugStringA(dramStr.c_str());
        OutputDebugStringA(pageFileStr.c_str());
        OutputDebugStringA("-----------------------------\n");
    }
    else {
        OutputDebugStringA("�޸� ���� ��ȸ ����\n");
    }
}

/// Trim unused resources
void ResourceManager::Trim() {
    dxgiDevice->Trim();
}

/// Texture2D Resource Create
shared_ptr<Texture2D> ResourceManager::CreateTexture2D(string filePath) 
{
    string key = filePath;
    auto it = map_texture2D.find(key);

    // map�� weak_ptr�� ���� ���
    if (it != map_texture2D.end())
    {
        // 1) �ν��Ͻ��� ����ִٸ� shared_ptr return
        if (!it->second.expired()) return it->second.lock();

        // �ν��Ͻ��� �Ҹ�Ȼ��¶�� weak_ptr�� �����ϰ� �� ���ҽ� ����
        else map_texture2D.erase(it);
    }

    // 2) Create new resource
    shared_ptr<Texture2D> new_texture2D = make_shared<Texture2D>();
    wstring wpath(filePath.begin(), filePath.end());

    // �� ���ڴ� ����
    ComPtr<IWICBitmapDecoder> decoder;
    HRESULT hr = wicImagingFactory->CreateDecoderFromFilename(
        wpath.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
    if (FAILED(hr)) {
        wcout << L"[ERROR] Decoder ���� ����: " << wpath << endl;
        return nullptr;
    }

    // �� ù ��° ������ ���
    ComPtr<IWICBitmapFrameDecode> frame;
    hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr)) {
        wcout << L"[ERROR] Frame �������� ����: " << wpath << endl;
        return nullptr;
    }

    // �� ���� ��ȯ�� ����
    ComPtr<IWICFormatConverter> converter;
    hr = wicImagingFactory->CreateFormatConverter(&converter);
    if (FAILED(hr)) {
        wcout << L"[ERROR] FormatConverter ���� ����: " << wpath << endl;
        return nullptr;
    }

    // �� ���� ��ȯ �ʱ�ȭ (32bppPBGRA)
    hr = converter->Initialize(
        frame.Get(),
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        nullptr,
        0.0f,
        WICBitmapPaletteTypeCustom
    );
    if (FAILED(hr)) {
        wcout << L"[ERROR] Format ��ȯ ����: " << wpath << endl;
        return nullptr;
    }

    // �� Bitmap �Ӽ� ����
    D2D1_BITMAP_PROPERTIES1 bmpProps = D2D1::BitmapProperties1(
        D2D1_BITMAP_OPTIONS_NONE,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
    );

    // �� Bitmap ����
    hr = RenderSystem::Get().renderTarget->CreateBitmapFromWicBitmap(
        converter.Get(), &bmpProps, &new_texture2D->texture2D);
    if (FAILED(hr)) {
        wcout << L"[ERROR] Bitmap ���� ����: " << wpath << endl;
        return nullptr;
    }

    // map�� �����ϰ� shared_ptr return
    map_texture2D[key] = new_texture2D;
    return new_texture2D;
}