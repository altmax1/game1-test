GamerDistAttack = function (Game)
Coords = Game:SelectTarget()
CoordX = math.floor(Coords/1000)
CoordY = math.fmod (Coords,1000)
WeaponID = Game:GetIdByGamerSlot(7)
BeastID = Game:GetBeastNumber (CoordX, CoordY)
if BeastID<0 then
	return
	end

Game:SetBeastHP (BeastID,-1)

end