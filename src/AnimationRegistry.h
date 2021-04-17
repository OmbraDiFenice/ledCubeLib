#ifndef __ANIMATIONREGISTRY_H__
#define __ANIMATIONREGISTRY_H__

#include <util/Vector.h>
#include <Animation.h>
#include <util/MyString.h>

#define REGISTER(ANIM_CLASS) AnimationRegistry::Registrar<ANIM_CLASS> _##ANIM_CLASS##_registrar

class AnimationRegistry {
    public:
        template<typename T>
        class Registrar {
            public:
                Registrar() {
                    _key = AnimationRegistry::GetInstance().add<T>();
                };
                inline unsigned int getKey() const { return _key; };
            private:
                unsigned int _key;
        };

    public:
        static AnimationRegistry& GetInstance();

        AnimationRegistry() = default;
        explicit AnimationRegistry(unsigned int initialCapacity) : _animations(initialCapacity) {};
        AnimationRegistry(const AnimationRegistry&) = delete;

        inline unsigned int size() const { return _animations.size(); }

        template<typename T>
        unsigned int add() {
            unsigned int key = _animations.size();
            _animations.append(new T());
            return key;
        };

        Animation* getById(unsigned int key);
        Animation* getByName(const MyString& name);

        MyString toString();

    private:
        Vector<Animation*> _animations;
};

#endif
