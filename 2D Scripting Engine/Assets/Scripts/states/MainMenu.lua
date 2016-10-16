MainMenu = { }


MainMenu.circle = tss.rendering.Circle(100.0);

function MainMenu.init()
    MainMenu.circle:SetFillColor(tss.gui.colors.Green);
end

function MainMenu.update(dt)

end

function MainMenu.draw()
    MainMenu.circle:Draw();
end

function MainMenu.keyCodePressed(key)
    local step = 20000;

    if key == tss.input.w then
        MainMenu.circle:SetPosY(MainMenu.circle:GetPosY() - step * tss.dt);
    end

    if key == tss.input.s then
        MainMenu.circle:SetPosY(MainMenu.circle:GetPosY() + step * tss.dt);
    end

    if key == tss.input.a then
        MainMenu.circle:SetPosX(MainMenu.circle:GetPosX() - step * tss.dt);
    end

    if key == tss.input.d then
        MainMenu.circle:SetPosX(MainMenu.circle:GetPosX() + step * tss.dt);
    end

end

function MainMenu.shutdown()
    MainMenu.circle = nil;
end



return MainMenu;
