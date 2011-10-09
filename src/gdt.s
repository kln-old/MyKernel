;
; Gdt.s -- contains global descriptor table and interrupt descriptor table
;          setup code.
;          Based on code from Bran's kernel development tutorials.
;          Rewritten for JamesM's kernel development tutorials.

[GLOBAL gdt_load]    ; Allows the C code to call gdt_flush().

gdt_load:
    mov eax, [esp+4]  ; Get the pointer to the GDT, passed as a parameter.
    lgdt [eax]        ; Load the new GDT pointer

    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax        ; Load all data segment selectors
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.load   ; 0x08 is the offset to our code segment: Far jump!
.load:
    ret

[GLOBAL idt_load]    ; Allows the C code to call idt_flush().

idt_load:
    mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter. 
    lidt [eax]        ; Load the IDT pointer.
    ret
