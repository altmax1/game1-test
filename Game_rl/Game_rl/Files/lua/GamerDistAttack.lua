GamerDistAttack = function (Game)
Coords = Game:SelectTarget()
CoordX = math.floor(Coords/1000)
CoordY = math.fmod (Coords,1000)
WeaponID = Game:GetIdByGamerSlot(7)
if WeaponID == -1 then --проверяем наличие оружия
	Game:PrintMessage ('У вас нет соответствующего оружия')
	return
end
BeastID = Game:GetBeastNumber (CoordX, CoordY)
Distance = ((Game.GamerX-CoordX)^2+(Game.GamerY-CoordY)^2)^0.5
WeaponRange = Game:GetWeaponRange (WeaponID)
if Distance>WeaponRange then -- проверяем дистанцию до цели
	Game:PrintMessage ('Ваше оружие недостаточно дальнобойно чтобы нанести урон по указанному месту')
	return
end
NeedsAmmo = Game:GetWeaponNeedsAmmo (WeaponID)
AmmoQuantity = Game:GetWeaponCurrentAmmuQuantity (WeaponID)
if NeedsAmmo == 1 and AmmoQuantity == 0 then -- проверяем патроны/заряды
	Game:PrintMessage ('Ваше оружие не заряжено. Зарядите его')
	return;
end
if BeastID<0 then
	return
	end

Game:SetBeastHP (BeastID,-1)

end