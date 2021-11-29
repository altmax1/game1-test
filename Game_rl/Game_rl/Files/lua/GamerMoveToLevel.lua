GamerMoveToLevel = function (Game, Level)

NumOfConnector = Game:GetConnectorNum(Game.GamerX, Game.GamerY)
if (Game:GetConnectorIsCompleted(NumOfConnector)) == 0 then
	CreateNewAndMove(Game,Level)
	Game:LevelRefresh()
end

if (Game:GetConnectorIsCompleted(NumOfConnector)) == 1 then
	MoveToNewLevel (Game)
end

end

CreateNewAndMove = function (Game, Level)
	OldX = Game.GamerX
	OldY = Game.GamerY
	OldZ = Game:GetLevelNum()
	NumOfConOld = Game:GetConnectorNum(Game.GamerX, Game.GamerY)
	NewX = 0
	NewY = 0
	NewZ = 0
	Game:CreateNewLevel()
	Game:LevelRefresh()
	levelwidth = Game:GetLevelWidth ()
	levelheight = Game:GetLevelHeight  ()
	ConnectorDone = 0
	for x = 1, levelwidth do
		for y = levelheight,1,-1 do
			if Game:GetTileBaseType (x,y) == "#" and Game:GetTileBaseType (x,y-1) == "." then
				Game:MakeNewConnector(x,y,OldX,OldY,OldZ,1, "portal", 1)
				ConnectorDone = 1
				Game.GamerX = x
				Game.GamerY = y-1
				NewX = x
				NewY = y
				break
			end
	
		end
		if ConnectorDone == 1 then
			break
		end
	end
	NewZ = Game:GetLevelNum()
	Game:SetCurrentLevel (OldZ)
	Game:LevelRefresh()
	Game:SetConnectorDestX (NumOfConOld, NewX)
	Game:SetConnectorDestY (NumOfConOld, NewY)
	Game:SetConnectorDestZ (NumOfConOld, NewZ)
	Game:SetConnectorIsCompleted (NumOfConOld, 1)
	Game:SetCurrentLevel (NewZ)
	Game:LevelRefresh()

end

MoveToNewLevel = function (Game)
NumOfConnector = Game:GetConnectorNum (Game.GamerX, Game.GamerY)
NewX = Game:GetConnectorDestX( NumOfConnector)
NewY = Game:GetConnectorDestY (NumOfConnector)
NewZ = Game:GetConnectorDestZ (NumOfConnector)
Game:SetCurrentLevel (NewZ)
Game:LevelRefresh ()
Game.GamerX = NewX
Game.GamerY = NewY


end