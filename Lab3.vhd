library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Lab3 is
	port (
		clk    : in std_logic := '0'; -- clk.clk
		rst : in std_logic := '0';  -- rst.reset_n
		i2c_0_export_scl_pad_io : inout std_logic := '0'; -- scl_pad_io
      i2c_0_export_sda_pad_io : inout std_logic := '0';  -- sda_pad_io
		cs_n : out std_logic := '1';
		alt_adr : out std_logic := '1'
	);
end entity Lab3;



architecture arch of Lab3 is

    component Lab3_qsys is
        port (
            clk_clk                 : in    std_logic := 'X'; -- clk
            rst_reset_n             : in    std_logic := 'X'; -- reset_n
            i2c_0_export_scl_pad_io : inout std_logic := 'X'; -- scl_pad_io
            i2c_0_export_sda_pad_io : inout std_logic := 'X'  -- sda_pad_io
        );
    end component Lab3_qsys;
	 
begin
    u0 : Lab3_qsys
        port map (
            clk_clk     => clk,     -- clk.clk
            rst_reset_n => rst, 		-- rst.reset_n 
				i2c_0_export_sda_pad_io => i2c_0_export_sda_pad_io,
				i2c_0_export_scl_pad_io => i2c_0_export_scl_pad_io
			);
	cs_n<='1';
	alt_adr<='1';
		  
end architecture;