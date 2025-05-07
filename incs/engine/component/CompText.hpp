#ifndef COMP_TEXT_HPP
# define COMP_TEXT_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

# define COMP_DEF_TEXT "UNDEFINED" //             NOTE : default content for the component
# define COMP_DEF_FONTSIZE 12 //                  NOTE : default font size for the component
# define COMP_DEF_COLOR { 255, 255, 255, 255 } // NOTE : default colour for the component
# define COMP_DEF_FONT "Arial" //                 NOTE : default font name for the component

# define COMP_DEF_MIN_TEXT_SIZE 1.0f //           NOTE : minimum font size for the component

class CompText : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		string _title;
		string _content;
		string _fontName; // NOTE : name of the font to draw
		float  _fontSize; // NOTE : size of the font to draw
		Color  _fontCol; //  NOTE : colour of the text to draw

	// ================================ CORE METHODS
		void onCpy( const CompText &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompText();

		CompText();
		CompText( Entity *Ntt,
			bool   isActive = COMP_DEF_ACTIVITY,
			string title    = COMP_DEF_TEXT,
			string content  = COMP_DEF_TEXT,
			float  fontSize = COMP_DEF_FONTSIZE,
			Color  fontCol  = COMP_DEF_COLOR
		);

		CompText( const CompText &rhs );
		CompText &operator=( const CompText &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_TEXT; }
		inline comp_type_e getType() const override { return COMP_TEXT; } // NOTE : overide this in derived classes

	// ================ STRING METHODS
		inline string getFullText() const { return _title + " : " + _content; }

		inline string getTitle() const { return _title; }
		inline bool voidTitle(){ _title = COMP_DEF_TEXT; return true; }
		inline bool setTitle(   string title ){ _title  = title; return true; }
		inline bool addToTitle( string title ){ _title += title; return true; }

		inline string getContent() const { return _content; }
		inline bool voidContent(){ _content = COMP_DEF_TEXT; return true; }
		inline bool setContent(   string content ){ _content  = content; return true; }
		inline bool addToContent( string content ){ _content += content; return true; }

	// ================ FONT METHODS

		inline string getFontName() const { return _fontName; }
		inline bool voidFontName(){ _fontName = COMP_DEF_FONT; return true; }
		inline bool setFontName(   string fontName ){ _fontName  = fontName; return true; }
		inline bool addToFontName( string fontName ){ _fontName += fontName; return true; }

		inline float getFontSize() const { return _fontSize; }
		inline bool voidFontSize(){ _fontSize = COMP_DEF_FONTSIZE; return true; }
		inline bool setFontSize( float fontSize ){ _fontSize = max( COMP_DEF_MIN_TEXT_SIZE, fontSize); return true; }
		inline bool changeFontSize( float delta ){ _fontSize = max( COMP_DEF_MIN_TEXT_SIZE, _fontSize + delta ); return true; }

		inline Color getFontCol() const { return _fontCol; }
		inline bool voidFontCol(){ _fontCol = COMP_DEF_COLOR; return true; } // NOTE : sets the Color to 0

		inline bool setFontCol( const Color &Col ){ _fontCol = Col; return true; }
		inline bool setFontCol( byte_t r, byte_t g, byte_t b, byte_t a ){ _fontCol.r = r; _fontCol.g = g; _fontCol.b = b; _fontCol.a = a; return true; }

		inline bool changeFontCol( const Color &delta ){ _fontCol.r += delta.r; _fontCol.g += delta.g; _fontCol.b += delta.b; _fontCol.a += delta.a; return true; }
		inline bool changeFontCol( byte_t dr, byte_t dg, byte_t db, byte_t da ){ _fontCol.r += dr; _fontCol.g += dg; _fontCol.b += db; _fontCol.a += da; return true; }

	// ================================ TICK METHODS
		inline bool onTick() override { return _active; } // NOTE : No additional behavior for CompText
};

#endif // COMP_TEXT_HPP

// TODO : implement the text component