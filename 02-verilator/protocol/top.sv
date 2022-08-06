`default_nettype none

module top (
  // Input
  input logic clk_i,
  input logic button_i,
  // Output
  output logic done_o
);

  logic req;
  logic busy;
  logic [3:0] counter;

  master master0 (
    .clk_i    (clk_i),
    .counter_i(counter),
    .busy_i   (busy),
    .button_i (button_i),
    .done_o   (done_o),
    .req_o    (req)
  );

  counter counter0 (
    .clk_i    (clk_i),
    .req_i    (req),
    .counter_o(counter),
    .busy_o   (busy)
  );



endmodule : top
