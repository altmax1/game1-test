MakeCreatures = function (LuaAdapter)
for i = 1,20 do
x = 0
y = 0
levelwidth = LuaAdapter:GetLevelWidth ()
levelheight = LuaAdapter:GetLevelHeight  ()
repeat
  x = LuaAdapter:MyRandom (levelwidth)
  y = LuaAdapter:MyRandom (levelheight)
until LuaAdapter:GetTileBaseType (x,y) == "."
print (x)
print (y)
LuaAdapter:CreateTheBeast (0, x, y)
end
end