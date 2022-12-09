# Cartwheel Readme #

To see some examples of bipedal motion control animations, the `./Demos` folder contains code files which replace the original `./src/interactControl.cpp` file to execute single and paired actor behaviors as described in the table below.

 | Executable Demos Source File  | Animation Description                                   |
 | :---------------------------- | :------------------------------------------------------ |
 |  interactControl_Demos1.cpp | A human character walking up to an upright box column and kicking it over. |
 |interactControl_Demos2.cpp | A human character walking from right to left and tripping over a box placed on the ground in his path of motion. |
 | interactControl_Exchange.cpp | Two human characters, where first both of them grab an object from a box, one of them kicks the box and then both exchange objects with each other. |
 | interactControl_GiveObj.cpp | Two human characters, where first one of them grabs an object from a box, kicks the box and then gives such object to the other person. |
 | interactControl_JumpBF.cpp | A human jump rotating Backwards or Forwards according to the code being activated (to jump rotating Backwards or Normally [with no rotation], the code from `./src/Behaviors/Jump.cpp` must be activated by uncommenting the lines that describe such jumps and commenting the lines of the jump that was being used). |
 | interactControl_JumpN.cpp | This makes the human to jump normally over a box. |
 | interactControl_Pull.cpp | The human character goes toward an object grabs the handle and tries to pull it some distance backwards. |
 | interactControl_Push.cpp | The human character walking toward a big box and then starts pushing it to some distance. |
 | interactControl_SitDown.cpp | The human character appears just in front of a box and starts executing the motions to sit down on such box. |
 | interactControl_ThrowCatch.cpp | Two human characters appears on the scene, one of them grabs an object from a box, then kicks such box, gives the object to another person in front of him and starts walking backwards, so the person that has the object tries to throw it toward the other and then the person that is going to receive the object, moves an arm in order to catch it. |

These demo animation executables, which require read access to animated motion control modeling and visualization asset files in the `./data` folder, should be invoked from the top-level `./ua-cartwheel` folder as:

````shell
    export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH; ./Demos/interactControl_{unique demo name}.exe
````

The executables are built using the `make all` (or `make demos`) process as described in the [README](./README.md) file.

To add any human in the scene and have it work with any specific behavior, make the following changes within the appropriate `interactControl.cpp` file:

First to define and add the human to the scene, the following lines of code are needed within the function `makeWorld(...)`:

````C++
    //Defining the human definition files and parameters
    string name = "Human1";
    string characterFile = "data/characters/bipV3.rbs";
    string controllerFile = "data/controllers/bipV3/HMV/compositeController.con";
    string actionFile = "data/controllers/bipV3/HMV/actions";
    Math::Point3d humanPosition(0, 0.95, -2.2);
    double heading = PI*0; //3.14;

    //Adding the human
    p_simulator->addHuman(name, characterFile, controllerFile, actionFile, humanPosition, heading);
    Math::Point3d humanPosition2(-0.4, 1.0, -0.25);
    p_simulator->addHuman("Human2", characterFile, controllerFile, actionFile, humanPosition2, 3.14);
````

After that, within the function `render(...)` and inside of the conditional that checks for options `if (nOpc == 0) {`, in order to add any behavior (e.g., walk), the following line must be used:

````C++
    g_simulator->doBehavior("Walk", "Human1", new Walk_Params(0, 4, 0.3, 3.14));
````

The syntax for adding any other behavior to any character is the following:

````C++
    g_simulator->doBehavior("NameBehavior", "NameHuman", 
       new NameBehavior_Params(InitTime,Duration, Other_BehaviorSpecificParams));
````

When adding two or more behaviors that starts at same time or while any other behavior is currently working, the simulator will try to automatically execute them in parallel if such attempted behavior allows it.

To change the skin character to the original one, just rename the file `bipV3-.rbs` to `bipV3.rbs` within the `./data/characters` folder.
