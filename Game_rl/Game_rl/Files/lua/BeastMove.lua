
BeastMove = function (Game, Beast)
--a = Game:LOS (Game.GamerX, Game.GamerY, Beast.CoordX, Beast.CoordY)
--c = Game:LOS (Beast.CoordX, Beast.CoordY, Game.GamerX, Game.GamerY)
--b = Game:PathFind (Beast.CoordX, Beast.CoordY,Game.GamerX, Game.GamerY)
--print (a, c)
Beast.MovePoints = Beast.MovePoints+Beast.Speed




MGamerX = Game.GamerX
MGamerY = Game.GamerY
MBeastX = Beast.CoordX
MBeastY = Beast.CoordY

distance = ((MGamerX-MBeastX)^2+(MGamerY-MBeastY)^2)^0.5 -- Расстояние между ГГ и мобом
if distance <= Beast.RangeOfSight then
	a = Game:LOS (Game.GamerX, Game.GamerY, Beast.CoordX, Beast.CoordY)
	c = Game:LOS (Beast.CoordX, Beast.CoordY, Game.GamerX, Game.GamerY)
	end
	
	AttackRange = math.max (Beast:GetAttackRange (1), Beast:GetAttackRange(2), Beast:GetAttackRange (3))


if a == 1 or c == 1 then  -- если моб видит ГГ
	if distance > AttackRange+1.5  then

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
		HaveMoved = Beast:Move (NextCoordX, NextCoordY,0)
		if HaveMoved == 0 then
			TryToMove (Game, Beast, Game.GamerX, Game.GamerY)
		end
		return
	end
	return
	end
	
	
	
	if distance <= AttackRange+1.5 then
		BeastAttack (Game, Beast, distance)
		return
	end
	
	
end

--if a==0 and c==0 and Beast.MovePoints >= 10 then
if Beast.MovePoints>=10 then

	MoveByMemory (Game, Beast)
	Beast.MovePoints = Beast.MovePoints-10
	return
end

--print (Beast.CoordX)
Beast.MovePoints = 10
end

BeastAttack = function (Game, Beast, distance)
	
	TempCoords = MGamerY*1000+MGamerX
	Beast:ClearAllSteps()
	Beast:SetNextStep (TempCoords)
	--Game.GamerHP = Game.GamerHP-1
	Beast.MovePoints = 10 --обнуляем счётчик скорости
	for i = 1,3 do
		AttackType = Beast:GetAttackType (i)
		if distance <= (Beast:GetAttackRange(i)+1.5) and AttackType ~= 0 then 
		GamerDefense = Game:GetGamerDefenseAdvansed (AttackType)
		MaxAttack = Beast:GetMaxAttack (i)
		MinAttack = Beast:GetMinAttack (i)
		AttackPower = MinAttack + Game:MyRandom (MaxAttack - MinAttack)
		Damage = AttackPower - GamerDefense
		if Damage < 0 then
			Damage = 0
		end	
		if AttackType == 1 then
		CType = "Физическим воздействием"
		end
		if AttackType == 2 then
		CType = "огнём и высокой температурой"
		end
		if AttackType == 3 then
		CType = "холодом"
		end
		if AttackType == 4 then
		CType = "негативной энергией хаоса"
		end
		if AttackType == 5 then
		CType = "ядом"
		end
		if AttackType == 6 then
		CType = "электричеством"
		end
		if AttackType == 7 then
		CType = "экстрасенсорными способностями"
		end
		if AttackType == 8 then
		CType = "кислотой"
		end
		if AttackType == 9 then
		CType = "агрессивной бактериологической и мутагенной средой"
		end
		if AttackType == 10 then
		CType = "радиоактивным излучением"
		end
		Game.GamerHP = Game.GamerHP-Damage
		Game:PrintMessage ("<<"..Beast.RName..">> нанес(ла) вам "..Damage.. " урона "..CType) 
		Game:AddMessageToLog ("<<"..Beast.RName..">> нанес(ла) вам "..Damage.. " урона "..CType)
		
		end
	end
	
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

if Beast:GetStepsSize()==0 then
	return
end
TempCoords1 = Beast:GetNextStep()
TempX = TempCoords1%1000
TempY = (TempCoords1-TempX)/1000
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
if a==1 or c == 1  then
	if distance<=Beast.RangeOfSight then
		TempCoords = MGamerY*1000+MGamerX
		Beast:ClearAllSteps()
		Beast:SetNextStep (TempCoords)
	end
end

end
