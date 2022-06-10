#include "TestUI.h"
#include "Device/GameDevice.h"


void TestUI::onStart() {
	
	//オブジェクト生成
	for (int i = 0; i < 5; i++)
	{
		healthStocks[i] = new GameObject(getUser().getGameMediator());
		healthStocksBlack[i] = new GameObject(getUser().getGameMediator());
	}
	accelerationGaugeFlame = new GameObject(getUser().getGameMediator());
	accelerationGaugeCore = new GameObject(getUser().getGameMediator());
	fuelGaugeObj = new GameObject(getUser().getGameMediator());
	accelerationEffect = new GameObject(getUser().getGameMediator());
	for (int i = 0; i < 100; i++)
	{
		accEffect.push_back(new GameObject(getUser().getGameMediator()));
	}
	//体力ゲージ
	for (int i = 0; i < 5; i++)
	{
		healthStocks[i]->getTransform().setLocalPosition(Vec3{ -600.0f+(100.0f*i),340,1 });
		healthStocksBlack[i]->getTransform().setLocalPosition(Vec3{ -600.0f + (100.0f * i),340,2 });
		healthStocksRenderer[i] = healthStocks[i]->addComponent<GUISpriteRenderer>();
		healthStocksBlackRenderer[i] = healthStocksBlack[i]->addComponent<GUISpriteRenderer>();
		healthStocksRenderer[i]->setTextureByName("healthStock");
		healthStocksBlackRenderer[i]->setTextureByName("healthStockBlack");
		healthStocks[i]->getTransform().setLocalScale(Vec3{64,64,1});
		healthStocksBlack[i]->getTransform().setLocalScale(Vec3{ 64,64,1 });
		healthStocksRenderer[i]->setActive(true);
		healthStocksBlackRenderer[i]->setActive(true);
	}
	//加速ゲージ
	accelerationGaugeFlame->getTransform().setLocalPosition(Vec3{ 350,-250,2 });
	accelerationGaugeFlame->getTransform().setLocalScale(Vec3{ 200,200,1 });
	accelerationGaugeFlameRenderer = accelerationGaugeFlame->addComponent<GUISpriteRenderer>();
	accelerationGaugeFlameRenderer->setTextureByName("accelerationGaugeFlame");
	accelerationGaugeCore->getTransform().setLocalPosition(Vec3{ 350,-350,1 });
	accelerationGaugeCore->getTransform().setLocalScale(Vec3{ 200,200,1 });
	accelerationGaugeCoreRenderer = accelerationGaugeCore->addComponent<GUISpriteRenderer>();
	accelerationGaugeCoreRenderer->setTextureByName("accelerationGaugeCore");
	//燃料ゲージ
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
	//初期座標からスケールの半分を引く
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
	//体力ストック描画管理
	for (int i = health+1; i <= MAX_HEALTH; i++)
	{
		healthStocksRenderer[i]->setActive(false);
	}
	//割合割り出し
	perAcceleration = acceleration / MAX_ACCELERATION;
	perFuel = fuel / MAX_FUEL;
	//割合から現在のゲージのサイズを計算
	float fuelGaugeSize = fuelGaugeScale * perFuel;
	//加速ゲージの角度計算
	accAdjustNum *= perAcceleration;
	//オブジェクトに反映
	fuelGaugeObj->getTransform().setLocalScale(Vec3{ 100,fuelGaugeSize,1 });
	accelerationGaugeCore->getTransform().setLocalAngles(Vec3{ 0,0,90-accAdjustNum });
}

