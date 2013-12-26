#pragma once
#ifndef _GTACHARACTER_HPP_
#define _GTACHARACTER_HPP_
#include <engine/GTAObject.hpp>
#include <bullet/BulletDynamics/Character/btKinematicCharacterController.h>
#include <bullet/btBulletCollisionCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <glm/glm.hpp>

class GTAVehicle;
class GameWorld;

/**
 * @brief The GTACharacter struct
 * Stores data relating to an instance of a "pedestrian".
 */
struct GTACharacter : public GTAObject
{
private:
	GTAVehicle* currentVehicle;
	size_t currentSeat;

	void createActor(const glm::vec3& size = glm::vec3(0.35f, 0.35f, 1.3f));
	void destroyActor();

public:

	enum Activity {
		None,
		Idle,
		Walk,
		Run,
		Crouch,
		Jump,
		Falling,
		Landing,
		VehicleDrive,
		VehicleSit,
		KnockedDown,
		GettingUp
	};

	std::shared_ptr<CharacterData> ped;

	btKinematicCharacterController* physCharacter;
	btPairCachingGhostObject* physObject;
	btCapsuleShapeZ* physShape;

	GTAAIController* controller;

	/**
	 * @brief GTACharacter Constructs a Character
	 * @param pos
	 * @param rot
	 * @param model
	 * @param ped PEDS_t struct to use.
	 */
	GTACharacter(GameWorld* engine, const glm::vec3& pos, const glm::quat& rot, Model* model, std::shared_ptr<CharacterData> data);

	~GTACharacter();

	Type type() { return Character; }

	Activity currentActivity;

	void changeAction(Activity newAction);

	void tick(float dt);

	/**
	 * @brief updateCharacter updates internall bullet Character.
	 */
	void updateCharacter();

	virtual void setPosition(const glm::vec3& pos);

	virtual glm::vec3 getPosition() const;
	
	bool enterVehicle(GTAVehicle* vehicle, size_t seat);

	GTAVehicle *getCurrentVehicle() const;
	size_t getCurrentSeat() const;
	void setCurrentVehicle(GTAVehicle *value, size_t seat);
	
    virtual bool takeDamage(const DamageInfo& damage);
	
	void jump();
	
	/**
	 * Resets the Actor to the nearest AI Graph node
	 * (taking into account the current vehicle)
	 */
	void resetToAINode();
};

#endif