.data
extern address : qword

.code
	AsmJump proc
		jmp qword ptr [address]
	AsmJump endp
end
