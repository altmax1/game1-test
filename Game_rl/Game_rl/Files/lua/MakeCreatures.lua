MakeCreatures = function (Game)
for i = 1,20 do
x = 0
y = 0
levelwidth = Game:GetLevelWidth ()
levelheight = Game:GetLevelHeight  ()
repeat
  x = Game:MyRandom (levelwidth)
  y = Game:MyRandom (levelheight)
until Game:GetTileBaseType (x,y) == "."

Game:CreateTheBeast (0, x, y)
end
end