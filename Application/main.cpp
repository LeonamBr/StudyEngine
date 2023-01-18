#include <Study.h>

class TestAPI : public Study::Application{

    public:
        TestAPI(){}
        ~TestAPI(){}

};

Study::Application* Study::CreateApplication(){

    return new TestAPI();
}