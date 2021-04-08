#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "CheckÑollision.h"
#include "Storage.h"
#include "Application.h"
#include "uploadingStringFromTxt.h"

int main()
{
    Applications App;
    App.GetStorage()->UploadScene("main scene.txt");
    //App.GetStorage()->GetObject("ball1")->AddComponent<TestScript>();

    App.Run();

    return 0;
}