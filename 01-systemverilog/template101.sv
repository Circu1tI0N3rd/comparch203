/*******************************************************************************
Creator:        Hai Cao Xuan (joachimcao@proton.me)

Additional Contributions by:
            1.  Name
            2.  Name

File Name:      <file name>
Design Name:    <design name>
Project Name:   <project name>
Description:    <description>
                <long description>

Changelog:      yyyy.mm.dd - <short changelog>
                             <long changelog>

*******************************************************************************/

/*******************************************************************************

Copyright (c) 2022 Hai Cao Xuan

*******************************************************************************/

`default_nettype none

// !! use spaces, not tabs, and one indent = 2 spaces
module my_module #(
  parameter Width = 80,
  parameter Height = 24
) (
  // Global
  input                     clk_i,
  input                     rst_ni,

  // Input
  input                     req_valid_i,
  input [Width-1:0]         req_data_i,
  input my_package::data_s  data_i

  // Output
  output                    req_ready_o,
  ...
);

  // Local Declarations
  logic [Width-1:0] req_data_masked;

  // Instantiations
  submodule u_submodule #(
    .Width(32)
  ) (
    .clk_i,
    .rst_ni,
    .req_valid_i,
    .req_data_i (req_data_masked),
    .req_ready_o(req_ready),
    ...
  );

  // Conbinational Logic
  always_comb begin
    req_data_masked = req_data_i;
    case (fsm_state_q)
      ST_IDLE: begin
        req_data_masked = req_data_i & MASK_IDLE;
        ...
  end

  ...

  // State Register

  ...

  // Output Logic

  ...

endmodule : my_module
