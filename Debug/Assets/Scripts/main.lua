
-- add aditional files / folders
package.path = package.path .. ";../2D Scripting Engine/Assets/Scripts/?.lua";
package.path = package.path .. ";../2D Scripting Engine/Assets/Scripts/enums/?.lua";


tss.frameCounter = 0;
tss.fps = 0;
tss.theTime = 0;
tss.dt = 0;

tss.testString1 = tss.gui.Text();

-- string for the console, should be moved out of script at some point
tss.consoleString = tss.gui.Text();

tss.circle = tss.rendering.Circle(100.0);
tss.img = tss.rendering.Sprite("Assets/Graphics/sapa-vietnam.jpg");


-- Reload a given package
function Reload(packageName)
	package.loaded[packageName] = nil;
	return require(packageName);
end

-- Reload all modules
function ReloadModules()
	require("color");
end

-- Require lua files
ReloadModules();


function tss.init()
    print("main.lua -- init()");

    tss.testString1:SetText("OK");
    tss.testString1:SetPosition(10, 50);
    tss.testString1:SetColor(tss.gui.colors.Red);

    tss.consoleString:SetText("");
    tss.consoleString:SetVisible(false);

    tss.circle:SetFillColor(tss.gui.colors.Green);
    --tss.circle:SetOutlineColor(tss.gui.colors.White);
    --tss.circle:SetOutlineThickness(10.0);
end


function tss.update(dt)
    --print("main.lua -- update(" .. dt .. ")");

    tss.dt = dt;
    tss.frameCounter = tss.frameCounter + 1;
    tss.theTime = tss.theTime + dt;

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

    tss.img:Draw();

    tss.circle:Draw();

    tss.testString1:Draw();

    if tss.consoleString:IsVisible() then
        tss.consoleString:Draw();
    end
end

function tss.keyCodePressed(key)
    print("main.lua -- keyCodePressed(" .. key .. ")");

    local step = 20000;

    if key == tss.input.w then
        tss.circle:SetPosY(tss.circle:GetPosY() - step * tss.dt);
    end

    if key == tss.input.s then
        tss.circle:SetPosY(tss.circle:GetPosY() + step * tss.dt);
    end

    if key == tss.input.a then
        tss.circle:SetPosX(tss.circle:GetPosX() - step * tss.dt);
    end

    if key == tss.input.d then
        tss.circle:SetPosX(tss.circle:GetPosX() + step * tss.dt);
    end

end

function tss.keyPressed(char)
    print("main.lua -- keyPressed(" .. char .. ")");

    if tss.consoleString:IsVisible() and '\r' ~= char and '\b' == char then
        local tmp = tss.consoleString:GetText();
        tmp = tmp:sub(1, -2)
        tss.consoleString:SetText(tmp);
    end

    if tss.consoleString:IsVisible() and '\r' ~= char and '\b' ~= char then
        tss.consoleString:SetText(tss.consoleString:GetText() .. char);
    end

    if '\r' == char then
        if tss.consoleString:IsVisible() then
            tss.scripting.RunString(tss.consoleString:GetText());
            tss.consoleString:SetText("");
        end
        tss.consoleString:SetVisible(not tss.consoleString:IsVisible());
    end

end


function tss.shutdown()
    print("main.lua -- shutdown()");

    tss.img = nil;
    tss.circle = nil
    tss.consoleString = nil;
    tss.testString1 = nil;
    tss.frameCounter = nil;
    tss.fps = nil;
    tss.theTime = nil;
end
