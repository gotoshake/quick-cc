local Role = class("Role", function()
    return display.newNode()
end

local Role = class("Role", function(roleIndex)
    if not rect then rect = CCRect(0, 0, 0, 0) end
    local node = display.newClippingRegionNode(rect)
    node:setNodeEventEnabled(true)
    require("framework.api.EventProtocol").extend(node)
    return node
end)

function initRole(resId, actionId, x, y, isFixed)

    local frames = display.newFrames(resIds[resId] .. "_" .. self.actionNames[actionId] .."_%02d.png", 1, self.actionNums[actionId])
    local sprite = display.newSprite(frames[1], x, y)
    -- 一定概率水平翻转
    if math.random(1, 2) == 1 then
        sprite:setFlipX(true)
    end
    if isFixed == nil then
        self.objs[#self.objs + 1] = sprite
    end
    -- 添加到player批渲染结点
    self.playerNode:addChild(sprite, self.MAX_ZORDER - y);
    -- 创建动画
    local animation = display.newAnimation(frames, math.random(1, 2) / 15)
    -- 播放动画
    sprite:playAnimationForever(animation)

end

