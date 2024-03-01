;---------------------------------------------------------------------
; LCD library
;
; 2nd March 2024
;---------------------------------------------------------------------

LCD_1:      .equ	80h
LCD_2:      .equ	0c0h
LCD_3:      .equ	94h
LCD_4:      .equ	0d4h

;---------------------------------------------------------------------
;
;---------------------------------------------------------------------
CLEAR_LCD:  rst		28h             ;  Wait for LCD to not be busy before...

            ld		a,01h           ;  ...sending the LCD clear command and...
            out		(04),a
            rst		28H             ;  ...wait for it to complete

            ret

;---------------------------------------------------------------------
;
;---------------------------------------------------------------------
HL_TO_ASC:  ld		bc,-10000       ;  Convert the 16 bit value in HL to it's ASCII equivalent
            call	HTA_1
            ld		bc,-1000
            call	HTA_1
            ld		bc,-100
            call	HTA_1
            ld		c,-10
            call	HTA_1
            ld		c,-1
HTA_1:      ld		a,'0'-1

HTA_2:      inc		a
            add		hl,bc
            jr		c,HTA_2
            sbc		hl,bc
            ld		c,14            ;  Send ASCII character to the LCD
            rst		10h
            ret

;---------------------------------------------------------------------
;
;---------------------------------------------------------------------
L_TO_ASC:   ld		h,0             ;  Convert the 8 bit value in L to it's ASCII equivalent
            ld		bc,-100
            call	LTA_1
            ld		c,-10
            call	LTA_1
            ld		c,-1

LTA_1:      ld		a,'0'-1

LTA_2:      inc		a
            add		hl,bc
            jr		c,LTA_2
            sbc		hl,bc
            ld		c,14            ;  Send ASCII character to the LCD
            rst		10h
            ret

