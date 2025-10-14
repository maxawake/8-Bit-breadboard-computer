# simple compiler for 8-bit computer

INSTRUCTIONS = {
    "NOP": 0b00000000,
    "LDA": 0b00010000,
    "ADD": 0b00100000,
    "SUB": 0b00110000,
    "STA": 0b01000000,
    "LDI": 0b01010000,
    "JMP": 0b01100000,
    "JC": 0b01110000,
    "JZ": 0b10000000,
    "OUT": 0b11100000,
    "HLT": 0b11110000,
    "VAR": None,  # special directive for defining data
}


def assemble(assembly_code):
    lines = assembly_code.strip().splitlines()
    machine_code = [0] * 256  # Initialize memory with 256 bytes
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
            # Handle regular instructions - opcode and operand in separate bytes
            opcode = INSTRUCTIONS[instr]
            machine_code[pc] = opcode
            pc += 1

            # If instruction has an operand, store it as the next byte
            if len(parts) > 1:
                operand = int(parts[1])
                if operand < 0 or operand > 255:
                    raise ValueError(f"Operand out of range (0-255): {operand}")
                machine_code[pc] = operand
                pc += 1

    return machine_code


if __name__ == "__main__":
    sample_code = """
    VAR 24 1
    VAR 26 0
    VAR 28 8
    VAR 30 8
    LDA 28
    SUB 24
    JC 10
    LDA 26
    OUT
    HLT
    STA 28
    LDA 26
    ADD 30
    STA 26
    JMP 0
    """
    machine_code = assemble(sample_code)
    i = 0
    while i < len(machine_code):
        code = machine_code[i]
        if code == 0:
            print(f"0b{code:08b}, // {i} - NOP")
            i += 1
        else:
            # Find instruction name
            instr_name = next((name for name, op in INSTRUCTIONS.items() if op == code), None)
            if instr_name:
                # Check if next byte is an operand
                if i + 1 < len(machine_code) and instr_name in ["LDA", "ADD", "SUB", "STA", "LDI", "JMP", "JC", "JZ"]:
                    operand = machine_code[i + 1]
                    print(f"0b{code:08b}, // {i} - ISTR: {instr_name}")
                    print(f"0b{operand:08b}, // {i + 1} - MEM: {operand}")
                    i += 2
                else:
                    print(f"0b{code:08b}, // {i} - {instr_name}")
                    i += 1
            else:
                print(f"0b{code:08b}, // {i} - DATA")
                i += 1
