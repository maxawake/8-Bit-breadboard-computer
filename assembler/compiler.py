# simple compiler for 8-bit computer

INSTRUCTIONS = {
    "NOP": 0b0000,
    "LDA": 0b0001,
    "ADD": 0b0010,
    "SUB": 0b0011,
    "STA": 0b0100,
    "LDI": 0b0101,
    "JMP": 0b0110,
    "JC": 0b0111,
    "JZ": 0b1000,
    "OUT": 0b1110,
    "HLT": 0b1111,
    "VAR": None,  # special directive for defining data
}


def assemble(assembly_code):
    lines = assembly_code.strip().splitlines()
    machine_code = [0] * 16  # Initialize memory with 16 bytes
    pc = 0  # Program counter

    for line in lines:
        parts = line.split()
        if len(parts) == 0:
            continue
        instr = parts[0].upper()
        if instr not in INSTRUCTIONS:
            raise ValueError(f"Unknown instruction: {instr}")

        if instr == "VAR":
            # Handle variable definition: VAR ADDR VALUE
            if len(parts) != 3:
                raise ValueError("VAR requires address and value")
            addr = int(parts[1])
            value = int(parts[2])
            if addr < 0 or addr > 255:
                raise ValueError(f"Address out of range (0-255): {addr}")
            if value < 0 or value > 255:
                raise ValueError(f"Value out of range (0-255): {value}")
            machine_code[addr] = value
        else:
            # Handle regular instructions
            opcode = INSTRUCTIONS[instr] << 4
            if len(parts) > 1:
                operand = int(parts[1])
                if operand < 0 or operand > 15:
                    raise ValueError(f"Operand out of range (0-15): {operand}")
                opcode |= operand
            machine_code[pc] = opcode
            pc += 1

    return machine_code


if __name__ == "__main__":
    sample_code = """
    VAR 12 1
    VAR 13 0
    VAR 14 8
    VAR 15 8
    LDA 14
    SUB 12
    JC 6
    LDA 13
    OUT
    HLT
    STA 14
    LDA 13
    ADD 15
    STA 13
    JMP 0
    """
    machine_code = assemble(sample_code)
    for addr, code in enumerate(machine_code):
        # Decode the instruction for display
        if code == 0:
            instr_name = "NOP"
        else:
            opcode = (code >> 4) & 0xF
            operand = code & 0xF
            instr_name = next((name for name, op in INSTRUCTIONS.items() if op == opcode), "UNKNOWN")
            if operand > 0:
                instr_name += f" {operand}"
        print(f"0b{code:08b}, // {addr} - {instr_name}")
