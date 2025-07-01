#include "ResourceManager.h"
#include "RenderSystem.h"
#include "Texture2D.h"


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