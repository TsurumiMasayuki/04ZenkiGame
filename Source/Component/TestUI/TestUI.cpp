#include "TestUI.h"
#include "Device/GameDevice.h"


void TestUI::onStart() {
	
	//�I�u�W�F�N�g����
	healthGaugeObj = new GameObject(getUser().getGameMediator());
	healthGaugeObj->setParent(&getUser().getGameMediator()->getMainCamera()->getUser());
	for (int i = 0; i < 5; i++)
	{
		healthStocks[i] = new GameObject(getUser().getGameMediator());
		healthStocks[i]->setParent(&getUser().getGameMediator()->getMainCamera()->getUser());
		healthSticksBlack[i] = new GameObject(getUser().getGameMediator());
		healthSticksBlack[i]->setParent(&getUser().getGameMediator()->getMainCamera()->getUser());
	}
	accelerationGaugeFlame = new GameObject(getUser().getGameMediator());
	accelerationGaugeFlame->setParent(&getUser().getGameMediator()->getMainCamera()->getUser());
	accelerationGaugeCore = new GameObject(getUser().getGameMediator());
	accelerationGaugeCore->setParent(&getUser().getGameMediator()->getMainCamera()->getUser());
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
	accelerationGaugeFlame->getTransform().setLocalPosition(Vec3{ 350,-250,2 });
	accelerationGaugeFlame->getTransform().setLocalScale(Vec3{ 200,200,1 });
	accelerationGaugeFlameRenderer = accelerationGaugeFlame->addComponent<GUISpriteRenderer>();
	accelerationGaugeFlameRenderer->setTextureByName("accelerationGaugeFlame");
	accelerationGaugeCore->getTransform().setLocalPosition(Vec3{ 350,-350,1 });
	accelerationGaugeCore->getTransform().setLocalScale(Vec3{ 200,200,1 });
	accelerationGaugeCoreRenderer = accelerationGaugeCore->addComponent<GUISpriteRenderer>();
	accelerationGaugeCoreRenderer->setTextureByName("accelerationGaugeCore");
	//�R���Q�[�W
	fuelGaugeObj->getTransform().setLocalPosition(Vec3{ 540,-350,1 });
	startFuelPos = fuelGaugeObj->getTransform().getLocalPosition();
	fuelGaugeObj->getTransform().setLocalScale(Vec3{ 100,400,1 });
	fuelGaugeScale = fuelGaugeObj->getTransform().getLocalScale().y;
	fuelGuiSpriteRenderer = fuelGaugeObj->addComponent<GUISpriteRenderer>();
	fuelGuiSpriteRenderer->setTextureByName("BoxFill");
	fuelGuiSpriteRenderer->setColor({ 1,1,0,1 });
	fuelGuiSpriteRenderer->setActive(true);	
	
}


void TestUI::onUpdate()
{
	accAdjustNum = 180.0f;
	//�������W����X�P�[���̔���������
	float healthScaleX = healthGaugeObj->getTransform().getLocalScale().x;
	healthGaugeObj->getTransform().setLocalPosition(Vec3{ startHealthPos.x + (healthScaleX / 2),startHealthPos.y,startHealthPos.z });
	float fuelScaleY = fuelGaugeObj->getTransform().getLocalScale().y;
	fuelGaugeObj->getTransform().setLocalPosition(Vec3{ startFuelPos.x,startFuelPos.y + (fuelScaleY / 2),startFuelPos.z });
	

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
	//�����Q�[�W�̊p�x�v�Z
	accAdjustNum *= perAcceleration;
	//�I�u�W�F�N�g�ɔ��f
	healthGaugeObj->getTransform().setLocalScale(Vec3{ healthGaugeSize,100,1 });
	fuelGaugeObj->getTransform().setLocalScale(Vec3{ 100,fuelGaugeSize,1 });
    
	accelerationGaugeCore->getTransform().setLocalAngles(Vec3{ 0,0,90-accAdjustNum });
}

