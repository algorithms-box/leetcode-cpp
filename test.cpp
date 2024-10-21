#include <iostream>
#include <memory>
#include <string.h>

class Entity {

  public:
    Entity() { std::cout << "Created Entity!" << std::endl; }

    ~Entity() { std::cout << "Destroyed Entity!" << std::endl; }
};

int main() {
    {
        std::shared_ptr<Entity> e0;
        {
            // std::unique_ptr<Entity> entity = std::make_unique<Entity>();
            std::unique_ptr<Entity> entity(new Entity());

            // 你不能这样做，因为unique_ptr的构造函数是explicit的
            // 你需要显式调用构造函数如上面的例子
            // std::unique_ptr<Entity> entity = new Entity();

            std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
            e0 = sharedEntity;
        }
    }
    std::cin.get();
    return 0;
}
