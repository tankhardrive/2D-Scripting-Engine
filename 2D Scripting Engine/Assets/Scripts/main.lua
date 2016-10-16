
-- add aditional files / folders
package.path = package.path .. ";../2D Scripting Engine/Assets/Scripts/?.lua";
package.path = package.path .. ";../2D Scripting Engine/Assets/Scripts/enums/?.lua";
package.path = package.path .. ";../2D Scripting Engine/Assets/Scripts/states/?.lua";


tss.frameCounter = 0;
tss.fps = 0;
tss.theTime = 0;

--tss.img = tss.rendering.Sprite("Assets/Graphics/sapa-vietnam.jpg");

-- Reload all modules
function tss.ReloadModules()
	require("color");
    States = require("States");
end

-- Require lua files
tss.ReloadModules();


function tss.init()
    print("main.lua -- init()");

    tss.SwitchState(States.MainMenu);
end


function tss.update(dt)
    --print("main.lua -- update(" .. dt .. ")");

    tss.frameCounter = tss.frameCounter + 1;
    tss.theTime = tss.theTime + dt;

    if tss.currentState.update ~= nil then
        tss.currentState.update(dt);
    end

    -- Calculate our FPS
    if tss.theTime >= 1 then
        tss.fps = tss.frameCounter;
        tss.frameCounter = 0;
        tss.theTime = 0;
    end

    -- Set our title with the FPS
    tss.engine.SetWindowTitle("2D Engine                [FPS: " .. tss.fps .. "]");
end


function tss.draw()
    --print("main.lua -- draw()");

    --tss.img:Draw();

    if tss.currentState.draw ~= nil then
        tss.currentState.draw();
    end
end

function tss.keyCodePressed(key)
    --print("main.lua -- keyCodePressed(" .. key .. ")");

    if tss.currentState.keyCodePressed ~= nil then
        tss.currentState.keyCodePressed(key);
    end

end

function tss.keyPressed(char)
    --print("main.lua -- keyPressed(" .. char .. ")");

    if tss.currentState.keyPressed ~= nil then
        tss.currentState.keyPressed(char);
    end

end


function tss.shutdown()
    print("main.lua -- shutdown()");

    if tss.currentState.shutdown ~= nil then
        tss.currentState.shutdown();
    end

    tss.img = nil;
    tss.frameCounter = nil;
    tss.fps = nil;
    tss.theTime = nil;
end
