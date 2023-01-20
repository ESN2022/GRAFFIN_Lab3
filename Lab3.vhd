library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Lab3 is
	port (
		clk    : in std_logic := '0'; -- clk.clk
		rst : in std_logic := '0';  -- rst.reset_n
		i2c_0_export_scl_pad_io : inout std_logic := '0'; -- scl_pad_io
      i2c_0_export_sda_pad_io : inout std_logic := '0';  -- sda_pad_io
		segment_out : out std_logic_vector(39 downto 0);
		pio1 : in std_logic :='0';
		cs_n : out std_logic := '1';
		alt_adr : out std_logic := '1'
	);
end entity Lab3;



architecture arch of Lab3 is

    component Lab3_qsys is
        port (
            clk_clk                 : in    std_logic := 'X'; -- clk
            rst_reset_n             : in    std_logic := 'X'; -- reset_n
				pio_0_export				: out   std_logic_vector(19 downto 0); --pio0
				pio_1_export				: in	  std_logic := 'X'; --pio1
            i2c_0_export_scl_pad_io : inout std_logic := 'X'; -- scl_pad_io
            i2c_0_export_sda_pad_io : inout std_logic := 'X'  -- sda_pad_io
        );
    end component Lab3_qsys;
	 
	 
	 component bin_to_7seg is
		port (
			pio_0 : in std_logic_vector(3 downto 0) ;
			segment : out std_logic_vector(7 downto 0) 
		);
	 end component bin_to_7seg;
	 
	 component bin_to_7seg_p is
		port (
			pio_0 : in std_logic_vector(3 downto 0) ;
			segment : out std_logic_vector(7 downto 0) 
		);
	 end component bin_to_7seg_p;
	 
	 signal pio_7seg : std_logic_vector(19 downto 0); 
	 
	 
begin
    u0 : Lab3_qsys
        port map (
            clk_clk     => clk,     -- clk.clk
            rst_reset_n => rst, 		-- rst.reset_n 
				pio_0_export => pio_7seg,
				pio_1_export => pio1,
				i2c_0_export_sda_pad_io => i2c_0_export_sda_pad_io,
				i2c_0_export_scl_pad_io => i2c_0_export_scl_pad_io
			);
			
	u1	:	bin_to_7seg
			port map(
				pio_0 => pio_7seg(3 downto 0),
				segment => segment_out(7 downto 0)
				);
		
	u2	:	bin_to_7seg
			port map(
				pio_0 => pio_7seg(7 downto 4),
				segment => segment_out(15 downto 8)
				);

	u3	:	bin_to_7seg
			port map(
				pio_0 => pio_7seg(11 downto 8),
				segment => segment_out(23 downto 16)
				);

	u4	:	bin_to_7seg_p
			port map(
				pio_0 => pio_7seg(15 downto 12),
				segment => segment_out(31 downto 24)
				);
				
	u5	:	bin_to_7seg
			port map(
				pio_0 => pio_7seg(19 downto 16),
				segment => segment_out(39 downto 32)
				);		
			
	cs_n<='1';
	alt_adr<='1';
	
	
		  
end architecture;