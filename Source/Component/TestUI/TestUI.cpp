#include "TestUI.h"
#include "Device/GameDevice.h"


void TestUI::onStart() {
	
	//�I�u�W�F�N�g����
	healthGaugeObj = new GameObject(getUser().getGameMediator());
	healthGaugeObj->setParent(&getUser().getGameMediator()->getMainCamera()->getUser());
	accelerationGaugeObj = new GameObject(getUser().getGameMediator());
	accelerationGaugeObj->setParent(&getUser().getGameMediator()->getMainCamera()->getUser());
	fuelGaugeObj = new GameObject(getUser().getGameMediator());
	fuelGaugeObj->setParent(&getUser().getGameMediator()->getMainCamera()->getUser());
	accelerationEffect = new GameObject(getUser().getGameMediator());
	accelerationEffect->setParent(&getUser().getGameMediator()->getMainCamera()->getUser());
	for (int i = 0; i < 100; i++)
	{
		accEffect.push_back(new GameObject(getUser().getGameMediator()));
		accEffect[i]->setParent(&getUser().getGameMediator()->getMainCamera()->getUser());
	}
	//�̗̓Q�[�W
	healthGaugeObj->getTransform().setLocalPosition(Vec3{ -500,340,1 });
	startHealthPos = healthGaugeObj->getTransform().getLocalPosition();
	healthGaugeObj->getTransform().setLocalScale(Vec3{ 1000,100,1 });
	healthGaugeScale = healthGaugeObj->getTransform().getLocalScale().x;
	healthGuiSpriteRenderer = healthGaugeObj->addComponent<GUISpriteRenderer>();
	healthGuiSpriteRenderer->setTextureByName("BoxFill");
	healthGuiSpriteRenderer->setColor({ 0,1,0,1 });
	healthGuiSpriteRenderer->setActive(true);
	//�����Q�[�W
	accelerationGaugeObj->getTransform().setLocalPosition(Vec3{ 540,-350,1 });
	startAccelerationPos = accelerationGaugeObj->getTransform().getLocalPosition();
	accelerationGaugeObj->getTransform().setLocalScale(Vec3{ 100,400,1 });
	accelerationGaugeScale = accelerationGaugeObj->getTransform().getLocalScale().y;
	accelerationGuiSpriteRenderer = accelerationGaugeObj->addComponent<GUISpriteRenderer>();
	accelerationGuiSpriteRenderer->setTextureByName("BoxFill");
	accelerationGuiSpriteRenderer->setColor({ 1,1,1,1 });
	accelerationGuiSpriteRenderer->setActive(true);
	//�R���Q�[�W
	fuelGaugeObj->getTransform().setLocalPosition(Vec3{ 440,-350,1 });
	startFuelPos = fuelGaugeObj->getTransform().getLocalPosition();
	fuelGaugeObj->getTransform().setLocalScale(Vec3{ 100,400,1 });
	fuelGaugeScale = fuelGaugeObj->getTransform().getLocalScale().y;
	fuelGuiSpriteRenderer = fuelGaugeObj->addComponent<GUISpriteRenderer>();
	fuelGuiSpriteRenderer->setTextureByName("BoxFill");
	fuelGuiSpriteRenderer->setColor({ 1,1,0,1 });
	fuelGuiSpriteRenderer->setActive(true);	
	//�����G�t�F�N�g
	accelerationEffect->getTransform().setLocalPosition(Vec3{ 0,0,50 });
	accelerationEffect->getTransform().setLocalScale(Vec3{ 1280,720,1 });
	accelerationEffectSpriteRenderer = accelerationEffect->addComponent<GUISpriteRenderer>();
	accelerationEffectSpriteRenderer->setTextureByName("accelerationEffect");
	accelerationEffectSpriteRenderer->setActive(true);
	for (int i = 0; i < 0; i++)
	{
		static int cnt = 0;
		if (i != 0)
		{
			accEffect[i]->getTransform().setLocalPosition(Vec3{ -360 + 64 * (i - cnt),0,0 });
			cnt += 1;
		}
		else
		{
			accEffect[i]->getTransform().setLocalPosition(Vec3{ -360,0,0 });
		}
		accEffectSpriteRenderer.push_back(accEffect[i]->addComponent<GUISpriteRenderer>());
		accEffectSpriteRenderer[i]->setActive(true);
		
	}
}

//�������W����X�P�[���̔���������
void TestUI::onUpdate()
{
	float healthScaleX = healthGaugeObj->getTransform().getLocalScale().x;
	healthGaugeObj->getTransform().setLocalPosition(Vec3{ startHealthPos.x + (healthScaleX / 2),startHealthPos.y,startHealthPos.z });
	float fuelScaleY = fuelGaugeObj->getTransform().getLocalScale().y;
	fuelGaugeObj->getTransform().setLocalPosition(Vec3{ startFuelPos.x,startFuelPos.y + (fuelScaleY / 2),startFuelPos.z });
	float accelerationScaleY = accelerationGaugeObj->getTransform().getLocalScale().y;

	/*if (!fuel)
	{
		assert(0);
	}
	if (!acceleration)
	{
		assert(0);
	}
	if (!health)
	{
		assert(0);
	}*/
	/*if (fuel)
	{
		fuel = 100;
	}
	if (acceleration)
	{
		acceleration = 1;
	}
	if (health)
	{
		health = 5;
	}*/
	//��������o��
	perHealth = health / MAX_HEALTH;
	perAcceleration = acceleration / MAX_ACCELERATION;
	perFuel = fuel / MAX_FUEL;
	//�������猻�݂̃Q�[�W�̃T�C�Y���v�Z
	float healthGaugeSize = healthGaugeScale * perHealth;
	float accelerationGaugeSize = accelerationGaugeScale * perAcceleration;
	float fuelGaugeSize = fuelGaugeScale * perFuel;
	//�I�u�W�F�N�g�ɔ��f
	healthGaugeObj->getTransform().setLocalScale(Vec3{ healthGaugeSize,100,1 });
	accelerationGaugeObj->getTransform().setLocalScale(Vec3{ 100,accelerationGaugeSize,1 });
	fuelGaugeObj->getTransform().setLocalScale(Vec3{ 100,fuelGaugeSize,1 });
	//�����G�t�F�N�g�̍X�V
	accelerationEffectSpriteRenderer->setColor({1,1,1,1.0f});
}

