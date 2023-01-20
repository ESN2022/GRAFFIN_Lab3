library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity bin_to_7seg is
	port (
		pio_0 : in std_logic_vector(3 downto 0);
		segment : out std_logic_vector(7 downto 0)
	);
end entity;

architecture arch of bin_to_7seg is
begin
process(pio_0)
	begin
		case pio_0 is
			when "0000" => segment <= "11000000"; -- "0"     
			when "0001" => segment <= "11111001"; -- "1" 
			when "0010" => segment <= "10100100"; -- "2" 
			when "0011" => segment <= "10110000"; -- "3" 
			when "0100" => segment <= "10011001"; -- "4" 
			when "0101" => segment <= "10010010"; -- "5" 
			when "0110" => segment <= "10000010"; -- "6" 
			when "0111" => segment <= "11111000"; -- "7" 
			when "1000" => segment <= "10000000"; -- "8"     
			when "1001" => segment <= "10010000"; -- "9"
			when "1111" => segment <= "10111111"; -- "-"
			when others => segment <= "11111111"; -- "X"
		end case;
	end process;
end architecture;