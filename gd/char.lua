require ("CharData")
local Char = class("Char")

function Char:ctor(index)
	self.data = CharData.get(index)
end

return Char
