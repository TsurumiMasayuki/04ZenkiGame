#include "CollectItemUI.h"
#include "Device/GameInput.h"

int CollectItemUI::count = -1;

void CollectItemUI::onStart()
{
	count = -1;
	//�X�v���C�g������
	for (int i = 0; i < 3; i++)
	{
		itemObj[i] = new GameObject(getUser().getGameMediator());
		CollectItemRenderer[i] = itemObj[i]->addComponent<GUISpriteRenderer>();
		CollectItemRenderer[i]->setTextureByName("collectItemF");
		itemObj[i]->getTransform().setLocalPosition(Vec3{ 400 + ((float)i * 90),330,1 });
		itemObj[i]->getTransform().setLocalScale(Vec3{ 64 });
		CollectItemRenderer[i]->setActive(false);
	}
}

void CollectItemUI::onUpdate()
{
	CollectItemRenderer[count]->setActive(true);
}
