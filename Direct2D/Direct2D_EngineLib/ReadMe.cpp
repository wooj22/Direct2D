

1. ��Ȱ���� ������ ������Ʈ���� ��͵��� ���� �ϴ°� ?
- Transform, RectTransform                           - World, UI
- SpriteRenderer, ImageRenderer                      - World, UI
- WorldTextRenderer, ScreenTextRenderer              - World, UI
- Button                                             - UI
- Animator
- Script
- Rigidbody, BoxCollider  // TODO :: ������



2. Transform�� �����ڴ� ? �ϳ��� ���ӿ�����Ʈ�� ��Ƽ Transform�� ����ϴ°� ? ���� Matrix����� ���� ?
- Transform�� ������Ʈ��, �ϳ��� ���ӿ�����Ʈ�� �ϳ��� Transform�� ������ ��(������� x)
- ���� matrix ����� TransformSystem���� transform�� dirty���� ��� �˾Ƽ� update����



3. �� ������ ������Ʈ�� �ٷ�� Manager or System�� ������ ?
- TransformSystem : ITransfrom(Transform, RectTransform) ������Ʈ �������̽� update()
- RenderSystem : IRenderer(SpriteRenderer, ImageRenderer, WorldTextRenderer, ScreenTextRenderer) ������Ʈ �������̽� update(), render()
���� �����Ŵ����� ��� �� ��ɱ��� �ϰ�����.
- ButtonSystem : Button ������Ʈ update() -> ���콺 Ŭ�� ���� üũ -> �̺�Ʈ �߻��� �ݹ�
- AnimatorSystem : ��ϵ� AnimatorController�� update()��Ű��, �������� SpriteRenderer�� sprite�� �ٲ���
- ScriptSystem : ����Ƽ �������̾�ó�� ����ǵ��� �����س���
- ColliderSystem :   // TODO :: ������
- RigidbodySystem :  // TODO :: ������

- Input : Input Static System
- Time : Time Static System

- ResourceManager : ���ҽ� ��Ȱ��, ����



4. ���� ������ ��ȣ�� RenderManager�� ��� �и��Ǿ��� ?
- ���� RenderSystem�� ���յǾ�����
- rigidbody, collider ���� ����� �и� ����(���� ��� �߰��� ����)




5. Scene�� ������ ������ �ΰ� ?
- GameObject �����̳� ����(����, ���� ����)
- ���� mainCamera�� ����� update��(Transform�� static���� ����Ǿ�����)




6. �ε��� ���ҽ� ��Ȱ�� ����� ?
 - class ResourceManager;
- Texture2D, Sprite ��Ȱ����
- // TODO :: AnimationClip�� ���ҽ��Ŵ������� �����ؼ� ��Ȱ���� ����




7. ���Ӽ���(��������Ʈ)�� ������ �κа� ����� ?
- class Button;->button OnClick() �̺�Ʈ ����



8. ���ӿ�����Ʈ �Ǵ� ������Ʈ�� �ּ� ��ȿ�� ������ � Ŭ�������� ����ϴ°� ?
- �������� �ֽ� ObjecTable �״�� ����
- // TODO :: ������Ʈ�� ����Ʈ ������ ������ ������ ����



9. �Է��� ��� ó���ϴ°� ?
 - class Input;
 - ���� Ŭ������ �����ؼ� �������� ���� ������ �� �ֵ��� ��


10. ���ӿ�����Ʈ�� ����� ����Ͽ��� ?
 - yes
 - ���� ������������ GameObject�� ��ӹ��� GameObject�� ����� ���ϴ´�� ������Ʈ�� �����Ͽ� ����ϰ���
 - ex) Cat.h -> ���� ��� ������ �������
 - ���������� ������ ���ӿ�����Ʈ(UI_Button, UI_Image, UI_Text) -> �˾Ƽ� ������Ʈ �����ǰ�, �Ŵ��� �ڵ� ��� ���ϴ´�� set�� �ϸ� ��


11. ������ ������ � Ŭ������ ����ϰų� �����Ͽ� �ۼ��Ͽ��� �ϴ°� ?
 - GameObject�� GameObject��ӹ޾Ƽ� ����
 - Animation�� AnimationClip�� ��ӹ޾� ���� clip�� �����ϰ�
	           AnimationBaseState�� ��ӹ޾� ���� state�� �����ϰ�
	           AnimatorController�� ��ӹ޾� ���ϴ� state�� �־� fsm �ӽ��� ����� ��



VVV �Ʒ��� ���� Ŭ������ �ֽ��ϴ� VVV



/*---------------------------------------------------------------------------------*/
/*--------------------- ���� ������ �ۼ��� �˾ƾ� �� Cycle -------------------------*/
/*-------------------------------------------------------------------------------*/

class GameObject;
{
	/* [GameObject Cycle] */		   // ! ��� �Ƚᵵ ��. ������ ���ӿ�����Ʈ ���� ��쿡 Script ������Ʈ�� ����� ������ ������ ���� ����Ŭ
	virtual void Awake() {};           // ������Ʈ�� ������ ��, ������ ����
	virtual void SceneStart() {};      // Scene�� Start -> Update�� SceneStart() ȣ�� ���� x
	virtual void Update() {};          // Scene�� Update
	virtual void Destroyed() {};       // Scene�� Exit, GameObject Delete
}

class Component;
{
	/* [Component Cycle] */
	virtual void OnEnable() = 0;	   // ������Ʈ Ȱ��ȭ��
	virtual void OnDestroy() = 0;	   // ������Ʈ or ���ӿ�����Ʈ �ı���
}

class Script;
{
	/* [script component cycle] */
	void OnEnable() override {}        // ������Ʈ Ȱ��ȭ��
	virtual void Awake() {}            // ������Ʈ�� ��� ������Ʈ�� ������ ���� ���� 1ȸ ȣ��
	virtual void Start() {}            // Awake() ���� ���� 1ȸ ȣ��
	virtual void Update() {}           // ������ ���� �ݺ� ȣ��
	virtual void FixedUpdate() {}      // ���� ������Ʈ 0.02f ���� �ݺ� ȣ��
	void OnDestroy() override {}       // ������Ʈ or ������Ʈ �Ҹ� ����

	// trigger
	virtual void OnTriggerEnter() {}
	virtual void OnTriggerStay() {}
	virtual void OnTriggerExit() {}

	// collision
	virtual void OnCollisionEnter() {}
	virtual void OnCollisionStay() {}
	virtual void OnCollisionExit() {}
}




/*---------------------------------------------------------------*/
/*---------------- ��Ȱ�� ������ Component ���� ------------------*/
/*--------------------------------------------------------------*/
class Transform;
class RectTransform;

class SpriteRenderer;
class ImageRenderer;
class WorldTextRenderer;
class ScreenTextRenderer;

class Button;
class Animator;
class Script;

//class BoxCollider;
//class Rigidbody;





/*---------------------------------------------------------------*/
/*------------------- Static System ���� ------------------------*/
/*--------------------------------------------------------------*/
class Input;
class Time;





/*------------------------------------------------------------*/
/*------------------ �׷��� ��ü ���� ------------------------*/
/*----------------------------------------------------------*/
class Texture2D;
class Sprite;





/*--------------------------------------------------------------*/
/*---------------- �̸� �����ص� GameObject --------------------*/
/*------------------------------------------------------------*/
class UI_Text;
class UI_Image;
class UI_Button;





/*-------------------------------------------------------------------*/
/*---------------------- Animatio FSM �ý��� ------------------------*/
/*------------------------------------------------------------------*/
/* Animator -> AnimatorController -> AnimationBaseState -> AnimationClip */

class Animator;						// "Component" ����� animator controller update, SpriteRenderer�� sprite�� ���� udpate
class AnimatorController;			// "�Ϲ� Class" ��ϵ� state�� ���� FSM �ý��� ��� -> current sprite update
class AnimationBaseState;			// "�Ϲ� Class" �� animation clip�� ���� state, Enter(), Update(), Eixt()�� transition �ڵ� �ۼ� ����
class AnimationClip;				// "�Ϲ� Class" animation clip asset


