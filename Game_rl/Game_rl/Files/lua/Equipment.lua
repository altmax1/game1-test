MakeSumOfEq = function (Game)

Defense = {0,0,0,0,0,0,0,0,0,0}
for def = 1,10 do
	for slot = 1,6 do
		Defense[def] = Defense[def]+ Game:GetDefenseBySlotAdvansed (slot, def)
	end
end
for i = 1,10 do
	Game:SetGamerDefenseAdbansed(i, Defense[1])
end

end