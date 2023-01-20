library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity bin_to_7seg_p is
	port (
		pio_0 : in std_logic_vector(3 downto 0);
		segment : out std_logic_vector(7 downto 0)
	);
end entity;

architecture arch of bin_to_7seg_p is
begin
process(pio_0)
	begin
		case pio_0 is
			when "0000" => segment <= "01000000"; -- "0"     
			when "0001" => segment <= "01111001"; -- "1" 
			when "0010" => segment <= "00100100"; -- "2" 
			when "0011" => segment <= "00110000"; -- "3" 
			when "0100" => segment <= "00011001"; -- "4" 
			when "0101" => segment <= "00010010"; -- "5" 
			when "0110" => segment <= "00000010"; -- "6" 
			when "0111" => segment <= "01111000"; -- "7" 
			when "1000" => segment <= "00000000"; -- "8"     
			when "1001" => segment <= "00010000"; -- "9"
			when others => segment <= "01111111"; -- "X"
		end case;
	end process;
end architecture;