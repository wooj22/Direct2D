
/*---------------------------------------------------------------------------------*/
/*--------------------- ���� ������ �ۼ��� �˾ƾ� �� Cycle -------------------------*/
/*-------------------------------------------------------------------------------*/

class GameObject;
{
	/* [GameObject Cycle] */		   
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


