#include "Classes/Manager.h"
#include "Classes/App.h"

using namespace std;

int main() {
    Manager information;
    App app(information);
    app.run();
    return 0;
}
