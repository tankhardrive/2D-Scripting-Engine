-- this file should be used for engine needed scripting functions
-- it should not be included with the other scripting files and should be embedded in the engine


io.write("Lua Version = ", _VERSION, "\n");


-- the current game state
tss.currentState = nil;
tss.nextState = nil;

-- Reload a given package
function Reload(packageName)
	package.loaded[packageName] = nil;
	return require(packageName);
end

-- Queue up the next state we want to switch to
-- it will be switched on the next update call
function tss.QueueState(newState)
    tss.nextState = newState;
end

-- Switch the current state
-- local as any place outside of this file should not instantly switch states
function tss.SwitchState(newState)
	if tss.currentState ~= nil then
		tss.currentState.shutdown();
		collectgarbage();

		tss.ReloadModules();
	end

    print("Loading " .. newState .. " state...");

	tss.currentState = Reload(newState);
    if tss.currentState.init ~= nil then
        tss.currentState.init();
    end
end

-- handle console input
function tss.ConsoleInput(char)

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

-- handle showing the console
function tss.ConsoleDraw()
    if tss.consoleString:IsVisible() then
        tss.consoleString:Draw();
    end
end
