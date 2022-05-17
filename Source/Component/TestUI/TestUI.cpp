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
	//�̗̓Q�[�W
	healthGaugeObj->getTransform().setLocalPosition(Vec3{ 0,340,1 });
	healthGaugeObj->getTransform().setLocalScale(Vec3{ 1000,100,1 });
	healthGaugeScale = healthGaugeObj->getTransform().getLocalScale().x;
	healthGuiSpriteRenderer = healthGaugeObj->addComponent<GUISpriteRenderer>();
	healthGuiSpriteRenderer->setTextureByName("BoxFill");
	healthGuiSpriteRenderer->setColor({ 0,1,0,1 });
	healthGuiSpriteRenderer->setActive(true);
	//�����Q�[�W
	accelerationGaugeObj->getTransform().setLocalPosition(Vec3{ 540,-150,1 });
	accelerationGaugeObj->getTransform().setLocalScale(Vec3{ 100,400,1 });
	accelerationGaugeScale = accelerationGaugeObj->getTransform().getLocalScale().y;
	accelerationGuiSpriteRenderer = accelerationGaugeObj->addComponent<GUISpriteRenderer>();
	accelerationGuiSpriteRenderer->setTextureByName("BoxFill");
	accelerationGuiSpriteRenderer->setColor({ 1,1,1,1 });
	accelerationGuiSpriteRenderer->setActive(true);
	//�R���Q�[�W
	fuelGaugeObj->getTransform().setLocalPosition(Vec3{ 440,-150,1 });
	fuelGaugeObj->getTransform().setLocalScale(Vec3{ 100,400,1 });
	fuelGaugeScale = fuelGaugeObj->getTransform().getLocalScale().y;
	fuelGuiSpriteRenderer = fuelGaugeObj->addComponent<GUISpriteRenderer>();
	fuelGuiSpriteRenderer->setTextureByName("BoxFill");
	fuelGuiSpriteRenderer->setColor({ 1,1,0,1 });
	fuelGuiSpriteRenderer->setActive(true);	
}

//�������W����X�P�[���̔���������
void TestUI::onUpdate()
{
	float ScaleY = fuelGaugeObj->getTransform().getLocalScale().y;
	float a = fuelGaugeObj->getTransform().getLocalPosition().y;
	fuelGaugeObj->getTransform().setLocalPosition(Vec3{ 0,ScaleY / 2 - a,1 });

	
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
	float healthGaugeSize =  healthGaugeScale * perHealth;
	float accelerationGaugeSize = accelerationGaugeScale * perAcceleration;
	float fuelGaugeSize = fuelGaugeScale * perFuel;
	//�I�u�W�F�N�g�ɔ��f
	healthGaugeObj->getTransform().setLocalScale(Vec3{ healthGaugeSize,100,1 });
	accelerationGaugeObj->getTransform().setLocalScale(Vec3{ 100,accelerationGaugeSize,1 });
	fuelGaugeObj->getTransform().setLocalScale(Vec3{ 100,fuelGaugeSize,1 });
}

