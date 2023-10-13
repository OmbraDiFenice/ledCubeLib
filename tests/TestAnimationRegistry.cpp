#include <TestAnimationRegistry.h>

TEST(TestAnimationRegistry, startEmpty) {
    ASSERT(0u == registry.size(), "size should be 0");
}

TEST(TestAnimationRegistry, add_template) {
    unsigned int key = registry.add<TestAnimation1>();
    ASSERT(1u == registry.size(), "size should increment");
    ASSERT(0u == key, "returned key should be the next one available");
}

TEST(TestAnimationRegistry, getById) {
    unsigned int key = registry.add<TestAnimation1>();

    ASSERT(0 == strcmp("TestAnimation1", registry.getById(key)->getName().get()), "unexpected animation");
}

TEST(TestAnimationRegistry, getById_multiple) {
    unsigned int key1 = registry.add<TestAnimation1>();
    unsigned int key2 = registry.add<TestAnimation2>();

    ASSERT(MyString("TestAnimation1") == registry.getById(key1)->getName(), "unexpected animation");
    ASSERT(MyString("TestAnimation2") == registry.getById(key2)->getName(), "unexpected animation");
}

TEST(TestAnimationRegistry, getById_notFound) {
    ASSERT(nullptr == registry.getById(0), "should be null");
    ASSERT(nullptr == registry.getById(100), "should be null");
}

TEST(TestAnimationRegistry, getByName) {
    registry.add<TestAnimation1>();
    registry.add<TestAnimation2>();

    ASSERT(MyString("TestAnimation1") == registry.getByName("TestAnimation1")->getName(), "unexpected animation");
    ASSERT(MyString("TestAnimation2") == registry.getByName("TestAnimation2")->getName(), "unexpected animation");
}

TEST(TestAnimationRegistry, getByName_multipleReturnsFirstRegistered) {
    unsigned int key1 = registry.add<TestAnimation1>();
    unsigned int key2 = registry.add<TestAnimation1>();

    ASSERT(registry.getById(key1) == registry.getByName("TestAnimation1"), "should return the first registered object corresponding to the provided name");
    ASSERT(registry.getById(key2) != registry.getByName("TestAnimation1"), "should return the first registered object corresponding to the provided name");
}

TEST(TestAnimationRegistry, getByName_notFound) {
    ASSERT(nullptr == registry.getByName("not-existent"), "should return null");
}

TEST(TestAnimationRegistry, toString) {
    registry.add<TestAnimation1>();
    registry.add<TestAnimation2>();

    MyString expectedOutput("0 - TestAnimation1\n\r1 - TestAnimation2\n\r");

    ASSERT(expectedOutput == registry.toString(), "should match");
}

TEST(TestAnimationRegistry, register_macro) {
    //AnimationRegistry::Registrar<TestAnimation1> _TestAnimation1_registrar;
    REGISTER(TestAnimation1);
    unsigned int key = _TestAnimation1_registrar.getKey();
    ASSERT(1u == AnimationRegistry::GetInstance().size(), "size should increment");
    ASSERT(0u == key, "returned key should be the next one available");
}
