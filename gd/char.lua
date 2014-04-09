require("framework.functions")

local char = class("char")

function char:ctor()
    self.str = 10
end

function char:attack()
    self.str = self.str-1
	print(self.str)
end

return char
