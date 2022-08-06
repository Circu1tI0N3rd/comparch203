module oneshot(
  input  wire clk_i,
  input  wire btn_i,
  output wire stb_o
  );

reg [1:0] state;
reg       stable;

assign stb_o = stable;

always @(posedge clk_i)
    begin
      case (state)
        0 : /* IDLE */
          if (btn_i)
          begin
            state  <= state + 1;
            stable <= 1;
          end
        1 : /* PRESS */
        begin
          stable <= 0;
          if (btn_i)
            state <= state + 1;
          else
            state <= 0;
        end
        2 : /* HOLD */
        begin
          if (!btn_i)
            state <= 0;
        end
        default : /* default */
        begin
          state  <= 0;
          stable <= 0;
        end
      endcase
    end

endmodule // debounce
