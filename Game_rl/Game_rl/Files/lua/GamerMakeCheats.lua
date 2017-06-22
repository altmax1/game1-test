GamerMakeCheats = function (Game)

Game:PrintMessageNow ('Введите команду...')
Command = Game:GetInputString()
if Command == "ADD_ITEM" then
	AddItemOnLevel (Game)
end

if Command == "ADD_BEAST" then
	AddBeastOnLevel (Game)
end


end

AddItemOnLevel = function (Game)

	Game:PrintMessageNow ("Введите ID вещи")
	ID = Game:GetInputNumber()
	if Game:CheckItemID (ID) == 0 then
		Game:PrintMessage ("Неправильный ID!!!!!")
		return
	end
	Game:PrintMessageNow ("Введите количество")
	Quantity = Game:GetInputNumber()
	Game:AddItemOnLevel (ID, Quantity, Game.GamerX, Game.GamerY)
	
end

AddBeastOnLevel = function (Game)

	Game:PrintMessageNow ("Введите ID моба")
	ID = Game:GetInputNumber ()
	if Game:CheckBeastID(ID) == 0 then
		Game:PrintMessage ("Несуществующий ID моба!!!")
		return;	
	end
	Game:PrintMessageNow ("Выберите место")
	Coords = Game:SelectTarget()
	if Coords > 1000000000 then
		Coords = Coords-1000000000
		OneShot = 1
	end

	CoordX = math.floor(Coords/1000)
	CoordY = math.fmod (Coords,1000)
	if Game:GetTileBaseType(CoordX,CoordY) ~= '.' then
		Game:PrintMessage ("Неправильное место!!!")
		return;
	end
	Game:CreateTheBeast (ID, CoordX, CoordY)

end





