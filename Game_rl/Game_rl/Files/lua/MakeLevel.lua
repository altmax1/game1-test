MakeLevel = function (Game, Level)
	print ("LevelNum".. Level:GetLevelNum())-- == 1 then -- делаем самый первый уровень
	Level:MakeDungeon (1,128,40,40)
	--MakeCreatures (Game)
	MakeConnector (Level, Game)
	MakeDepots(Game)
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

MakeDepots = function (Game)
NumOfRooms = Game:GetLevelNumOfRooms();
for i = 1,20 do
	Room = Game:MyRandom (NumOfRooms)
	LeftX = Game:GetRoomLeftX(Room)
	UpY = Game:GetRoomUpY(Room)
	RoomWidth = Game:GetRoomWidth(Room)
	RoomHeight = Game:GetRoomHeight(Room)
	CoordX = LeftX + Game:MyRandom (RoomWidth)
	CoordY = UpY+Game:MyRandom(RoomHeight)

	repeat
		CoordX = CoordX+1
	until 
		Game:GetTileBaseType (CoordX, CoordY) == '#'
	Game:SetLevelTile (CoordX, CoordY, 2000)

end
end