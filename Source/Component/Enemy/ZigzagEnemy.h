#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"

class Zigzagenemy
	: AbstractComponent
{
public:
	// AbstractComponent ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void onStart() override;
	virtual void onUpdate() override;

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	/// <param name="position">À•W</param>
	/// <param name="speedY">‰¡ˆÚ“®—Í</param>
	/// <param name="speedZ">‰œˆÚ“®—Í</param>
	/// <param name="radius">‰~“›”¼Œa</param>
	void init(Vec3 position, float speedY, float speedZ, float radius = 11.0f);

	/// <summary>
	/// Ü‚è•Ô‚µ
	/// </summary>
	void wrap();

private:
	Vec3 position{};
	Vec3 velocity{};
	float radius = 0;

	int dir = false;

	Timer wrapTimer;
};