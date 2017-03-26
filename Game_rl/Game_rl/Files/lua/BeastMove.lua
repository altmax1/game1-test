
BeastMove = function (Game, Beast)
a = Game:LOS (Game.GamerX, Game.GamerY, Beast.CoordX, Beast.CoordY)
c = Game:LOS (Beast.CoordX, Beast.CoordY, Game.GamerX, Game.GamerY)
b = Game:PathFind (Beast.CoordX, Beast.CoordY,Game.GamerX, Game.GamerY)
print (a)
print ("GamerX: ", Game.GamerX, "GamerY: ", Game.GamerY)
print ("NumOfCreature", Game:GetBeastNumber (Beast.CoordX, Beast.CoordY))
if a == 1 or c == 1 then

dx = (Beast.CoordX-Game.GamerX)*-1
dy = (Beast.CoordY-Game.GamerY)*-1
print (dx, "  ", dy)
Num = Game:GetBeastNumber (Beast.CoordX, Beast.CoordY)
--Game:RemoveCreature (Num)
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
--Game:SetCreature (Beast.CoordX, Beast.CoordY, Num)	
Beast:Move (NextCoordX, NextCoordY,0)
end

print (Beast.CoordX)

end