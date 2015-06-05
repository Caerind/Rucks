#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <memory>
#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

class World;

class GameObject : public sf::Transformable, public sf::Drawable
{
    public:
        typedef std::shared_ptr<GameObject> Ptr;

        GameObject(World& world);

        static unsigned int getTypeId();

        void setId(unsigned int id);
        unsigned int getId() const;

        void setName(std::string const& name);
        std::string getName() const;

        void setTexture(std::string const& filename);
        void setTextureRect(sf::IntRect rect);

        virtual void handleEvent(sf::Event const& event);
        virtual void update(sf::Time dt);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        World& getWorld();

        bool isValid();

    protected:
        World& mWorld;

        sf::Sprite mSprite;

        unsigned int mId;
        std::string mName;
};

#endif // GAMEOBJECT_HPP
