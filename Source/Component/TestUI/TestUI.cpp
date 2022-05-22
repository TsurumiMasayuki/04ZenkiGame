#include "TestUI.h"
#include "Device/GameDevice.h"


void TestUI::onStart() {
	
	//オブジェクト生成
	healthGaugeObj = new GameObject(getUser().getGameMediator());
	healthGaugeObj->setParent(&getUser().getGameMediator()->getMainCamera()->getUser());
	accelerationGaugeObj = new GameObject(getUser().getGameMediator());
	accelerationGaugeObj->setParent(&getUser().getGameMediator()->getMainCamera()->getUser());
	fuelGaugeObj = new GameObject(getUser().getGameMediator());
	fuelGaugeObj->setParent(&getUser().getGameMediator()->getMainCamera()->getUser());
	accelerationEffect = new GameObject(getUser().getGameMediator());
	accelerationEffect->setParent(&getUser().getGameMediator()->getMainCamera()->getUser());
	//体力ゲージ
	healthGaugeObj->getTransform().setLocalPosition(Vec3{ -500,340,1 });
	startHealthPos = healthGaugeObj->getTransform().getLocalPosition();
	healthGaugeObj->getTransform().setLocalScale(Vec3{ 1000,100,1 });
	healthGaugeScale = healthGaugeObj->getTransform().getLocalScale().x;
	healthGuiSpriteRenderer = healthGaugeObj->addComponent<GUISpriteRenderer>();
	healthGuiSpriteRenderer->setTextureByName("BoxFill");
	healthGuiSpriteRenderer->setColor({ 0,1,0,1 });
	healthGuiSpriteRenderer->setActive(true);
	//加速ゲージ
	accelerationGaugeObj->getTransform().setLocalPosition(Vec3{ 540,-350,1 });
	startAccelerationPos = accelerationGaugeObj->getTransform().getLocalPosition();
	accelerationGaugeObj->getTransform().setLocalScale(Vec3{ 100,400,1 });
	accelerationGaugeScale = accelerationGaugeObj->getTransform().getLocalScale().y;
	accelerationGuiSpriteRenderer = accelerationGaugeObj->addComponent<GUISpriteRenderer>();
	accelerationGuiSpriteRenderer->setTextureByName("BoxFill");
	accelerationGuiSpriteRenderer->setColor({ 1,1,1,1 });
	accelerationGuiSpriteRenderer->setActive(true);
	//燃料ゲージ
	fuelGaugeObj->getTransform().setLocalPosition(Vec3{ 440,-350,1 });
	startFuelPos = fuelGaugeObj->getTransform().getLocalPosition();
	fuelGaugeObj->getTransform().setLocalScale(Vec3{ 100,400,1 });
	fuelGaugeScale = fuelGaugeObj->getTransform().getLocalScale().y;
	fuelGuiSpriteRenderer = fuelGaugeObj->addComponent<GUISpriteRenderer>();
	fuelGuiSpriteRenderer->setTextureByName("BoxFill");
	fuelGuiSpriteRenderer->setColor({ 1,1,0,1 });
	fuelGuiSpriteRenderer->setActive(true);	
	//加速エフェクト
	accelerationEffect->getTransform().setLocalPosition(Vec3{ 0,0,100 });
	accelerationEffect->getTransform().setLocalScale(Vec3{ 1280,720,1 });
	accelerationEffectSpriteRenderer = accelerationEffect->addComponent<GUISpriteRenderer>();
	accelerationEffectSpriteRenderer->setTextureByName("accelerationEffect");
	accelerationEffectSpriteRenderer->setActive(true);
}

//初期座標からスケールの半分を引く
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
	//割合割り出し
	perHealth = health / MAX_HEALTH;
	perAcceleration = acceleration / MAX_ACCELERATION;
	perFuel = fuel / MAX_FUEL;
	//割合から現在のゲージのサイズを計算
	float healthGaugeSize = healthGaugeScale * perHealth;
	float accelerationGaugeSize = accelerationGaugeScale * perAcceleration;
	float fuelGaugeSize = fuelGaugeScale * perFuel;
	//オブジェクトに反映
	healthGaugeObj->getTransform().setLocalScale(Vec3{ healthGaugeSize,100,1 });
	accelerationGaugeObj->getTransform().setLocalScale(Vec3{ 100,accelerationGaugeSize,1 });
	fuelGaugeObj->getTransform().setLocalScale(Vec3{ 100,fuelGaugeSize,1 });
	//加速エフェクトの更新
	accelerationEffectSpriteRenderer->setColor({1,1,1,1.0f});
}

