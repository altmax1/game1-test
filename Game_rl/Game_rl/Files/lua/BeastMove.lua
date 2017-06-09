
BeastMove = function (Game, Beast)
--a = Game:LOS (Game.GamerX, Game.GamerY, Beast.CoordX, Beast.CoordY)
--c = Game:LOS (Beast.CoordX, Beast.CoordY, Game.GamerX, Game.GamerY)
--b = Game:PathFind (Beast.CoordX, Beast.CoordY,Game.GamerX, Game.GamerY)
--print (a, c)
Beast.MovePoints = Beast.MovePoints+Beast.Speed
--if Beast.MovePoints < 10 then --учитываем скорость
--	return
--end

--Beast.MovePoints = Beast.MovePoints - 10 --делаем ход - вычитаем 10 очков движения
MGamerX = Game.GamerX
MGamerY = Game.GamerY
MBeastX = Beast.CoordX
MBeastY = Beast.CoordY

distance = ((MGamerX-MBeastX)^2+(MGamerY-MBeastY)^2)^0.5 -- Расстояние между ГГ и мобом
if distance < Beast.RangeOfSight then
	a = Game:LOS (Game.GamerX, Game.GamerY, Beast.CoordX, Beast.CoordY)
	c = Game:LOS (Beast.CoordX, Beast.CoordY, Game.GamerX, Game.GamerY)
	end

if a == 1 or c == 1 then  -- если моб видит ГГ
	if distance > 1.5 and distance<= Beast.RangeOfSight then
	TempCoords = MGamerY*1000+MGamerX
	Beast:ClearAllSteps()
	Beast:SetNextStep (TempCoords)
	dx = (Beast.CoordX-Game.GamerX)*-1
	dy = (Beast.CoordY-Game.GamerY)*-1
	Num = Game:GetBeastNumber (Beast.CoordX, Beast.CoordY)
	NextCoordX = Beast.CoordX
	NextCoordY = Beast.CoordY
		if dx > 0 then
			NextCoordX = Beast.CoordX+1
		end
		if dx < 0 then
			NextCoordX = Beast.CoordX-1
		end
		if dy > 0 then
			NextCoordY = Beast.CoordY+1
		end
		if dy < 0 then
			NextCoordY = Beast.CoordY-1
		end
	if Beast.MovePoints>=10 then
		Beast.MovePoints = Beast.MovePoints-10
		print (Beast.MovePoints)
		HaveMoved = Beast:Move (NextCoordX, NextCoordY,0)
		if HaveMoved == 0 then
			TryToMove (Game, Beast, Game.GamerX, Game.GamerY)
		end
		return
	end
	return
	end
	
	if distance < 1.5 then
		BeastAttack (Game, Beast)
		return
	end
	print ("GamerHP", Game.GamerHP)
	
end

if a==0 and c==0 then
	MoveByMemory (Game, Beast)
	return
end

--print (Beast.CoordX)
Beast.MovePoints = 10
end

BeastAttack = function (Game, Beast)
	print ("UnderAttack!!!")
	TempCoords = MGamerY*1000+MGamerX
	Beast:ClearAllSteps()
	Beast:SetNextStep (TempCoords)
	Game.GamerHP = Game.GamerHP-1
end

TryToMove = function (Game, Beast, DestX, DestY)
way = Game:PathFind (Beast.CoordX, Beast.CoordY, DestX, DestY)
if way == 1 then
Beast:Move (Beast.CoordX-1, Beast.CoordY-1,0)
end
if way == 2 then
Beast:Move (Beast.CoordX, Beast.CoordY-1,0)
end
if way == 3 then
Beast:Move (Beast.CoordX+1, Beast.CoordY-1,0)
end
if way == 4 then
Beast:Move (Beast.CoordX-1, Beast.CoordY,0)
end
if way == 6 then
Beast:Move (Beast.CoordX+1, Beast.CoordY,0)
end
if way == 7 then
Beast:Move (Beast.CoordX-1, Beast.CoordY+1,0)
end
if way == 8 then
Beast:Move (Beast.CoordX, Beast.CoordY+1,0)
end
if way == 9 then
Beast:Move (Beast.CoordX+1, Beast.CoordY+1,0)
end
end

MoveByMemory = function (Game, Beast)
--print ("Size of NextSteps",Beast:GetStepsSize())
if Beast:GetStepsSize()==0 then
	return
end
TempCoords1 = Beast:GetNextStep()
TempX = TempCoords1%1000
TempY = (TempCoords1-TempX)/1000
print ("NextStepX:", TempX, "NextStepY:", TempY)
print ("BeastX:", Beast.CoordX, "BeastY:", Beast.CoordY)
dx = (Beast.CoordX-TempX)*-1
dy = (Beast.CoordY-TempY)*-1
Num = Game:GetBeastNumber (Beast.CoordX, Beast.CoordY)
	NextCoordX = Beast.CoordX
	NextCoordY = Beast.CoordY
		if dx > 0 then
			NextCoordX = Beast.CoordX+1
		end
		if dx < 0 then
			NextCoordX = Beast.CoordX-1
		end
		if dy > 0 then
			NextCoordY = Beast.CoordY+1
		end
		if dy < 0 then
			NextCoordY = Beast.CoordY-1
		end
	HaveMoved = Beast:Move (NextCoordX, NextCoordY,0)
	if HaveMoved == 0 then
	print ("I cant MOVE!!!!!")
	TryToMove (Game, Beast, TempX, TempY)
	end
TempCoords1 = Beast:GetNextStep()
TempX = TempCoords1%1000
TempY = (TempCoords1-TempX)/1000
if TempX == Beast.CoordX and TempY == Beast.CoordY then
Beast:ClearAllSteps()
end
a = Game:LOS (Game.GamerX, Game.GamerY, Beast.CoordX, Beast.CoordY)
c = Game:LOS (Beast.CoordX, Beast.CoordY, Game.GamerX, Game.GamerY)
if a==1 or c == 1 then
TempCoords = MGamerY*1000+MGamerX
	Beast:ClearAllSteps()
	Beast:SetNextStep (TempCoords)
end

end
