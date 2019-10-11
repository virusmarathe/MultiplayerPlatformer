#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class EntityManager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> 
inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update(float dt) {}
	virtual void draw() {}

	virtual ~Component() {}

};

class Entity
{
public:

	Entity(EntityManager& man) : manager(man) {}
	void update(float dt)
	{
		for (auto& c : components) c->update(dt);
	}

	void draw()
	{
		for (auto& c : components) c->draw();
	}

	bool isActive() { return active; }
	void destroy() { active = false; }

	bool hasGroup(Group group)
	{
		return groupBitset[group];
	}

	void addGroup(Group group);

	void delGroup(Group group)
	{
		groupBitset[group] = false;
	}

	template <typename T>
	bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();

		return *c;
	}

	template<typename T>
	T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}


private:
	EntityManager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitset groupBitset;

};

class EntityManager
{
public:
	void update(float dt)
	{
		for (auto& e : entities) { e->update(dt); }
	}
	void draw()
	{
		for (auto& e : entities) { e->draw(); }
	}

	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);

			v.erase(std::remove_if(std::begin(v), std::end(v), 
				[i](Entity* entity)
				{
					return !entity->isActive() || !entity->hasGroup(i);
				}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}), 
			std::end(entities));
	}

	void addToGroup(Entity* entity, Group group)
	{
		groupedEntities[group].emplace_back(entity);
	}

	std::vector<Entity*>& getGroup(Group group)
	{
		return groupedEntities[group];
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));

		return *e;
	}
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
};