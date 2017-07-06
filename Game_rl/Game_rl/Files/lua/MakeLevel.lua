MakeLevel = function (Game, Level)
	print ("LevelNum".. Level:GetLevelNum())-- == 1 then -- ������ ����� ������ �������
	Level:MakeDungeon (1,128,40,40)
	--MakeCreatures (Game)
	MakeConnector (Level, Game)
	--end
end

MakeCreatures = function (Game)
for i = 1,10 do
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

MakeConnector = function (Level, Game)

levelwidth = Game:GetLevelWidth ()
levelheight = Game:GetLevelHeight  ()
ConnectorDone = 0
for x = 1, levelwidth do
	for y = 1, levelheight do
		if Game:GetTileBaseType (x,y) == "#" and Game:GetTileBaseType (x,y+1) == "." then
			Level: MakeNewConnector(x,y,0,0,0,1, "portal", 0)
			ConnectorDone = 1
			break
		end
	
	end
	if ConnectorDone == 1 then
		break
	end
end

end