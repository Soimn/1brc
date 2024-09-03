global ReadFullSpeed@@16

section .text

ReadFullSpeed@@16:
  xor r8, r8
  align 64
  .loop:
    lea rax, [rdx + r8]
    vmovdqa ymm0, [rax +   0]
    vmovdqa ymm0, [rax +  32]
    vmovdqa ymm0, [rax +  64]
    vmovdqa ymm0, [rax +  96]
    vmovdqa ymm0, [rax + 128]
    vmovdqa ymm0, [rax + 160]
    vmovdqa ymm0, [rax + 192]
    vmovdqa ymm0, [rax + 224]
    vmovdqa ymm0, [rax + 256]
    vmovdqa ymm0, [rax + 288]
    vmovdqa ymm0, [rax + 320]
    vmovdqa ymm0, [rax + 352]
    vmovdqa ymm0, [rax + 384]
    vmovdqa ymm0, [rax + 416]
    vmovdqa ymm0, [rax + 448]
    vmovdqa ymm0, [rax + 480]
  
    add r8, 512
    cmp r8, rcx
    jb .loop
  ret
