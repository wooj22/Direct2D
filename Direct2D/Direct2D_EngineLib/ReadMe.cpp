

/* GameObject Cycle */
virtual void Awake() {};           // ������Ʈ�� ������ ��, ������ ����
virtual void SceneStart() {};      // Scene�� Start -> Update�� SceneStart() ȣ�� ���� x
virtual void Update() {};          // Scene�� Update
virtual void Destroyed() {};       // Scene�� Exit, GameObject Delete

/* Component Cycle */
virtual void OnEnable() = 0;	   // ������Ʈ Ȱ��ȭ��
virtual void OnDestroy() = 0;	   // ������Ʈ or ���ӿ�����Ʈ �ı���

/* script component cycle */
void OnEnable() override {}        // ������Ʈ Ȱ��ȭ��
virtual void Awake() {}            // ������Ʈ�� ��� ������Ʈ�� ������ ���� ���� 1ȸ ȣ��
virtual void Start() {}            // Awake() ���� ���� 1ȸ ȣ��
virtual void Update() {}           // ������ ���� �ݺ� ȣ��
virtual void FixedUpdate() {}      // ���� ������Ʈ 0.02f ���� �ݺ� ȣ��
void OnDestroy() override {}       // ������Ʈ or ������Ʈ �Ҹ� ����