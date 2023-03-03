library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

library work;
use work.apu_consts.all;

entity apu_note_to_frequency is port (
	-- clk : in std_logic;
	-- rst : in std_logic;
	data : in std_logic_vector(6 downto 0);
	freq : out std_logic_vector(11 downto 0)); -- frequency
end entity;

architecture Behavioral of apu_note_to_frequency is
	signal buff : std_logic_vector(11 downto 0) := (others => '0');
	signal shift : integer;
begin

    shift <= to_integer(unsigned( data(2 downto 0) ));

    buff <= 
        x"1F0" when data(6 downto 3) = (x"1") else -- C     496 --values are calculated for 8kHz sample rate
        x"1D0" when data(6 downto 3) = (x"2") else -- C#/Db 464
        x"1B0" when data(6 downto 3) = (x"3") else -- D     432
        x"1A0" when data(6 downto 3) = (x"4") else -- D#/Eb 416
        x"180" when data(6 downto 3) = (x"5") else -- E     384
        x"170" when data(6 downto 3) = (x"6") else -- F     368
        x"158" when data(6 downto 3) = (x"7") else -- F#/Gb 344
        x"140" when data(6 downto 3) = (x"8") else -- G     320
        x"130" when data(6 downto 3) = (x"9") else -- G#/Ab 304
        x"120" when data(6 downto 3) = (x"A") else -- A     288
        x"110" when data(6 downto 3) = (x"B") else -- A#/Bb 272
        x"100" when data(6 downto 3) = (x"C") else -- B     256
        x"000";

    freq <= std_logic_vector(shift_right(unsigned(buff), shift));

end architecture;
