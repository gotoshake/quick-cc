local RoleInfo = class("RoleInfo", function()
    return display.newSprite()
end)

function RoleInfo:ctor()


	-- create menu
    local backButton = ui.newTTFLabel({
        text = "name",
        size = 16,
        x = display.left + 100,
        y = display.top - 30,
        align = ui.TEXT_ALIGN_CENTER,
    })

    self:addChild(backButton)

    local backButton = ui.newTTFLabel({
        text = "acc",
        size = 16,
        x = display.left + 100,
        y = display.top - 60,
        align = ui.TEXT_ALIGN_CENTER,
    })

    self:addChild(backButton)

    local backButton = ui.newTTFLabel({
        text = "hello world",
        size = 16,
        x = display.left + 100,
        y = display.top - 90,
        align = ui.TEXT_ALIGN_CENTER,
    })

    self:addChild(backButton)
end

return RoleInfo
