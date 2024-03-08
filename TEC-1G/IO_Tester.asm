            .org    4000h

START:      in      a,(0fbh)
            out     (0fbh),a
            jr      START

            .end