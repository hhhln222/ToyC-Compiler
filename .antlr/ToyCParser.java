// Generated from /home/hln/ToyC_compiler_antlr4/src/ToyC.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class ToyCParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		INT=1, VOID=2, IF=3, ELSE=4, WHILE=5, BREAK=6, CONTINUE=7, RETURN=8, OR=9, 
		AND=10, LT=11, GT=12, LE=13, GE=14, EQ=15, NE=16, ADD=17, SUB=18, MUL=19, 
		DIV=20, MOD=21, NOT=22, ASSIGN=23, SEMI=24, COMMA=25, LPAREN=26, RPAREN=27, 
		LBRACE=28, RBRACE=29, ID=30, NUMBER=31, LINE_COMMENT=32, COMMENT=33, WS=34;
	public static final int
		RULE_compUnit = 0, RULE_funcDef = 1, RULE_param = 2, RULE_stmt = 3, RULE_block = 4, 
		RULE_expr = 5, RULE_lOrExpr = 6, RULE_lAndExpr = 7, RULE_relExpr = 8, 
		RULE_addExpr = 9, RULE_mulExpr = 10, RULE_unaryExpr = 11, RULE_primaryExpr = 12;
	private static String[] makeRuleNames() {
		return new String[] {
			"compUnit", "funcDef", "param", "stmt", "block", "expr", "lOrExpr", "lAndExpr", 
			"relExpr", "addExpr", "mulExpr", "unaryExpr", "primaryExpr"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'int'", "'void'", "'if'", "'else'", "'while'", "'break'", "'continue'", 
			"'return'", "'||'", "'&&'", "'<'", "'>'", "'<='", "'>='", "'=='", "'!='", 
			"'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'='", "';'", "','", "'('", 
			"')'", "'{'", "'}'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "INT", "VOID", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "RETURN", 
			"OR", "AND", "LT", "GT", "LE", "GE", "EQ", "NE", "ADD", "SUB", "MUL", 
			"DIV", "MOD", "NOT", "ASSIGN", "SEMI", "COMMA", "LPAREN", "RPAREN", "LBRACE", 
			"RBRACE", "ID", "NUMBER", "LINE_COMMENT", "COMMENT", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "ToyC.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public ToyCParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class CompUnitContext extends ParserRuleContext {
		public List<FuncDefContext> funcDef() {
			return getRuleContexts(FuncDefContext.class);
		}
		public FuncDefContext funcDef(int i) {
			return getRuleContext(FuncDefContext.class,i);
		}
		public CompUnitContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_compUnit; }
	}

	public final CompUnitContext compUnit() throws RecognitionException {
		CompUnitContext _localctx = new CompUnitContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_compUnit);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(27); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(26);
				funcDef();
				}
				}
				setState(29); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==INT || _la==VOID );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FuncDefContext extends ParserRuleContext {
		public TerminalNode ID() { return getToken(ToyCParser.ID, 0); }
		public TerminalNode LPAREN() { return getToken(ToyCParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(ToyCParser.RPAREN, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public TerminalNode INT() { return getToken(ToyCParser.INT, 0); }
		public TerminalNode VOID() { return getToken(ToyCParser.VOID, 0); }
		public List<ParamContext> param() {
			return getRuleContexts(ParamContext.class);
		}
		public ParamContext param(int i) {
			return getRuleContext(ParamContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(ToyCParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(ToyCParser.COMMA, i);
		}
		public FuncDefContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_funcDef; }
	}

	public final FuncDefContext funcDef() throws RecognitionException {
		FuncDefContext _localctx = new FuncDefContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_funcDef);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(31);
			_la = _input.LA(1);
			if ( !(_la==INT || _la==VOID) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(32);
			match(ID);
			setState(33);
			match(LPAREN);
			setState(42);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==INT) {
				{
				setState(34);
				param();
				setState(39);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==COMMA) {
					{
					{
					setState(35);
					match(COMMA);
					setState(36);
					param();
					}
					}
					setState(41);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
			}

			setState(44);
			match(RPAREN);
			setState(45);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ParamContext extends ParserRuleContext {
		public TerminalNode INT() { return getToken(ToyCParser.INT, 0); }
		public TerminalNode ID() { return getToken(ToyCParser.ID, 0); }
		public ParamContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_param; }
	}

	public final ParamContext param() throws RecognitionException {
		ParamContext _localctx = new ParamContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_param);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(47);
			match(INT);
			setState(48);
			match(ID);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StmtContext extends ParserRuleContext {
		public StmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt; }
	 
		public StmtContext() { }
		public void copyFrom(StmtContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ContinueStmtContext extends StmtContext {
		public TerminalNode CONTINUE() { return getToken(ToyCParser.CONTINUE, 0); }
		public TerminalNode SEMI() { return getToken(ToyCParser.SEMI, 0); }
		public ContinueStmtContext(StmtContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class IfStmtContext extends StmtContext {
		public TerminalNode IF() { return getToken(ToyCParser.IF, 0); }
		public TerminalNode LPAREN() { return getToken(ToyCParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(ToyCParser.RPAREN, 0); }
		public List<StmtContext> stmt() {
			return getRuleContexts(StmtContext.class);
		}
		public StmtContext stmt(int i) {
			return getRuleContext(StmtContext.class,i);
		}
		public TerminalNode ELSE() { return getToken(ToyCParser.ELSE, 0); }
		public IfStmtContext(StmtContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ExprStmtContext extends StmtContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(ToyCParser.SEMI, 0); }
		public ExprStmtContext(StmtContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class WhileStmtContext extends StmtContext {
		public TerminalNode WHILE() { return getToken(ToyCParser.WHILE, 0); }
		public TerminalNode LPAREN() { return getToken(ToyCParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(ToyCParser.RPAREN, 0); }
		public StmtContext stmt() {
			return getRuleContext(StmtContext.class,0);
		}
		public WhileStmtContext(StmtContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class AssignStmtContext extends StmtContext {
		public TerminalNode ID() { return getToken(ToyCParser.ID, 0); }
		public TerminalNode ASSIGN() { return getToken(ToyCParser.ASSIGN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(ToyCParser.SEMI, 0); }
		public AssignStmtContext(StmtContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class BreakStmtContext extends StmtContext {
		public TerminalNode BREAK() { return getToken(ToyCParser.BREAK, 0); }
		public TerminalNode SEMI() { return getToken(ToyCParser.SEMI, 0); }
		public BreakStmtContext(StmtContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class BlockStmtContext extends StmtContext {
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public BlockStmtContext(StmtContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class EmptyStmtContext extends StmtContext {
		public TerminalNode SEMI() { return getToken(ToyCParser.SEMI, 0); }
		public EmptyStmtContext(StmtContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class DeclStmtContext extends StmtContext {
		public TerminalNode INT() { return getToken(ToyCParser.INT, 0); }
		public TerminalNode ID() { return getToken(ToyCParser.ID, 0); }
		public TerminalNode ASSIGN() { return getToken(ToyCParser.ASSIGN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(ToyCParser.SEMI, 0); }
		public DeclStmtContext(StmtContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ReturnStmtContext extends StmtContext {
		public TerminalNode RETURN() { return getToken(ToyCParser.RETURN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(ToyCParser.SEMI, 0); }
		public ReturnStmtContext(StmtContext ctx) { copyFrom(ctx); }
	}

	public final StmtContext stmt() throws RecognitionException {
		StmtContext _localctx = new StmtContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_stmt);
		try {
			setState(89);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
			case 1:
				_localctx = new BlockStmtContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(50);
				block();
				}
				break;
			case 2:
				_localctx = new EmptyStmtContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(51);
				match(SEMI);
				}
				break;
			case 3:
				_localctx = new ExprStmtContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(52);
				expr();
				setState(53);
				match(SEMI);
				}
				break;
			case 4:
				_localctx = new AssignStmtContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(55);
				match(ID);
				setState(56);
				match(ASSIGN);
				setState(57);
				expr();
				setState(58);
				match(SEMI);
				}
				break;
			case 5:
				_localctx = new DeclStmtContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(60);
				match(INT);
				setState(61);
				match(ID);
				setState(62);
				match(ASSIGN);
				setState(63);
				expr();
				setState(64);
				match(SEMI);
				}
				break;
			case 6:
				_localctx = new IfStmtContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(66);
				match(IF);
				setState(67);
				match(LPAREN);
				setState(68);
				expr();
				setState(69);
				match(RPAREN);
				setState(70);
				stmt();
				setState(73);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
				case 1:
					{
					setState(71);
					match(ELSE);
					setState(72);
					stmt();
					}
					break;
				}
				}
				break;
			case 7:
				_localctx = new WhileStmtContext(_localctx);
				enterOuterAlt(_localctx, 7);
				{
				setState(75);
				match(WHILE);
				setState(76);
				match(LPAREN);
				setState(77);
				expr();
				setState(78);
				match(RPAREN);
				setState(79);
				stmt();
				}
				break;
			case 8:
				_localctx = new BreakStmtContext(_localctx);
				enterOuterAlt(_localctx, 8);
				{
				setState(81);
				match(BREAK);
				setState(82);
				match(SEMI);
				}
				break;
			case 9:
				_localctx = new ContinueStmtContext(_localctx);
				enterOuterAlt(_localctx, 9);
				{
				setState(83);
				match(CONTINUE);
				setState(84);
				match(SEMI);
				}
				break;
			case 10:
				_localctx = new ReturnStmtContext(_localctx);
				enterOuterAlt(_localctx, 10);
				{
				setState(85);
				match(RETURN);
				setState(86);
				expr();
				setState(87);
				match(SEMI);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BlockContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(ToyCParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(ToyCParser.RBRACE, 0); }
		public List<StmtContext> stmt() {
			return getRuleContexts(StmtContext.class);
		}
		public StmtContext stmt(int i) {
			return getRuleContext(StmtContext.class,i);
		}
		public BlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_block; }
	}

	public final BlockContext block() throws RecognitionException {
		BlockContext _localctx = new BlockContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(91);
			match(LBRACE);
			setState(95);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 3578135018L) != 0)) {
				{
				{
				setState(92);
				stmt();
				}
				}
				setState(97);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(98);
			match(RBRACE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExprContext extends ParserRuleContext {
		public LOrExprContext lOrExpr() {
			return getRuleContext(LOrExprContext.class,0);
		}
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
	}

	public final ExprContext expr() throws RecognitionException {
		ExprContext _localctx = new ExprContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_expr);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(100);
			lOrExpr(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class LOrExprContext extends ParserRuleContext {
		public LOrExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_lOrExpr; }
	 
		public LOrExprContext() { }
		public void copyFrom(LOrExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class MulLOrExprContext extends LOrExprContext {
		public LOrExprContext lOrExpr() {
			return getRuleContext(LOrExprContext.class,0);
		}
		public TerminalNode OR() { return getToken(ToyCParser.OR, 0); }
		public LAndExprContext lAndExpr() {
			return getRuleContext(LAndExprContext.class,0);
		}
		public MulLOrExprContext(LOrExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class SingleLOrContext extends LOrExprContext {
		public LAndExprContext lAndExpr() {
			return getRuleContext(LAndExprContext.class,0);
		}
		public SingleLOrContext(LOrExprContext ctx) { copyFrom(ctx); }
	}

	public final LOrExprContext lOrExpr() throws RecognitionException {
		return lOrExpr(0);
	}

	private LOrExprContext lOrExpr(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		LOrExprContext _localctx = new LOrExprContext(_ctx, _parentState);
		LOrExprContext _prevctx = _localctx;
		int _startState = 12;
		enterRecursionRule(_localctx, 12, RULE_lOrExpr, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			_localctx = new SingleLOrContext(_localctx);
			_ctx = _localctx;
			_prevctx = _localctx;

			setState(103);
			lAndExpr(0);
			}
			_ctx.stop = _input.LT(-1);
			setState(110);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new MulLOrExprContext(new LOrExprContext(_parentctx, _parentState));
					pushNewRecursionContext(_localctx, _startState, RULE_lOrExpr);
					setState(105);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(106);
					match(OR);
					setState(107);
					lAndExpr(0);
					}
					} 
				}
				setState(112);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class LAndExprContext extends ParserRuleContext {
		public LAndExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_lAndExpr; }
	 
		public LAndExprContext() { }
		public void copyFrom(LAndExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class SingleLAndContext extends LAndExprContext {
		public RelExprContext relExpr() {
			return getRuleContext(RelExprContext.class,0);
		}
		public SingleLAndContext(LAndExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class MulLAndExprContext extends LAndExprContext {
		public LAndExprContext lAndExpr() {
			return getRuleContext(LAndExprContext.class,0);
		}
		public TerminalNode AND() { return getToken(ToyCParser.AND, 0); }
		public RelExprContext relExpr() {
			return getRuleContext(RelExprContext.class,0);
		}
		public MulLAndExprContext(LAndExprContext ctx) { copyFrom(ctx); }
	}

	public final LAndExprContext lAndExpr() throws RecognitionException {
		return lAndExpr(0);
	}

	private LAndExprContext lAndExpr(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		LAndExprContext _localctx = new LAndExprContext(_ctx, _parentState);
		LAndExprContext _prevctx = _localctx;
		int _startState = 14;
		enterRecursionRule(_localctx, 14, RULE_lAndExpr, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			_localctx = new SingleLAndContext(_localctx);
			_ctx = _localctx;
			_prevctx = _localctx;

			setState(114);
			relExpr(0);
			}
			_ctx.stop = _input.LT(-1);
			setState(121);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,7,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new MulLAndExprContext(new LAndExprContext(_parentctx, _parentState));
					pushNewRecursionContext(_localctx, _startState, RULE_lAndExpr);
					setState(116);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(117);
					match(AND);
					setState(118);
					relExpr(0);
					}
					} 
				}
				setState(123);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,7,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RelExprContext extends ParserRuleContext {
		public RelExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_relExpr; }
	 
		public RelExprContext() { }
		public void copyFrom(RelExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class SingleRelContext extends RelExprContext {
		public AddExprContext addExpr() {
			return getRuleContext(AddExprContext.class,0);
		}
		public SingleRelContext(RelExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class MulRelExprContext extends RelExprContext {
		public RelExprContext relExpr() {
			return getRuleContext(RelExprContext.class,0);
		}
		public AddExprContext addExpr() {
			return getRuleContext(AddExprContext.class,0);
		}
		public TerminalNode LT() { return getToken(ToyCParser.LT, 0); }
		public TerminalNode GT() { return getToken(ToyCParser.GT, 0); }
		public TerminalNode LE() { return getToken(ToyCParser.LE, 0); }
		public TerminalNode GE() { return getToken(ToyCParser.GE, 0); }
		public TerminalNode EQ() { return getToken(ToyCParser.EQ, 0); }
		public TerminalNode NE() { return getToken(ToyCParser.NE, 0); }
		public MulRelExprContext(RelExprContext ctx) { copyFrom(ctx); }
	}

	public final RelExprContext relExpr() throws RecognitionException {
		return relExpr(0);
	}

	private RelExprContext relExpr(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		RelExprContext _localctx = new RelExprContext(_ctx, _parentState);
		RelExprContext _prevctx = _localctx;
		int _startState = 16;
		enterRecursionRule(_localctx, 16, RULE_relExpr, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			_localctx = new SingleRelContext(_localctx);
			_ctx = _localctx;
			_prevctx = _localctx;

			setState(125);
			addExpr(0);
			}
			_ctx.stop = _input.LT(-1);
			setState(132);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,8,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new MulRelExprContext(new RelExprContext(_parentctx, _parentState));
					pushNewRecursionContext(_localctx, _startState, RULE_relExpr);
					setState(127);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(128);
					_la = _input.LA(1);
					if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 129024L) != 0)) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(129);
					addExpr(0);
					}
					} 
				}
				setState(134);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,8,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AddExprContext extends ParserRuleContext {
		public AddExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_addExpr; }
	 
		public AddExprContext() { }
		public void copyFrom(AddExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class MulAddExprContext extends AddExprContext {
		public AddExprContext addExpr() {
			return getRuleContext(AddExprContext.class,0);
		}
		public MulExprContext mulExpr() {
			return getRuleContext(MulExprContext.class,0);
		}
		public TerminalNode ADD() { return getToken(ToyCParser.ADD, 0); }
		public TerminalNode SUB() { return getToken(ToyCParser.SUB, 0); }
		public MulAddExprContext(AddExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class SingleAddContext extends AddExprContext {
		public MulExprContext mulExpr() {
			return getRuleContext(MulExprContext.class,0);
		}
		public SingleAddContext(AddExprContext ctx) { copyFrom(ctx); }
	}

	public final AddExprContext addExpr() throws RecognitionException {
		return addExpr(0);
	}

	private AddExprContext addExpr(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		AddExprContext _localctx = new AddExprContext(_ctx, _parentState);
		AddExprContext _prevctx = _localctx;
		int _startState = 18;
		enterRecursionRule(_localctx, 18, RULE_addExpr, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			_localctx = new SingleAddContext(_localctx);
			_ctx = _localctx;
			_prevctx = _localctx;

			setState(136);
			mulExpr(0);
			}
			_ctx.stop = _input.LT(-1);
			setState(143);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,9,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new MulAddExprContext(new AddExprContext(_parentctx, _parentState));
					pushNewRecursionContext(_localctx, _startState, RULE_addExpr);
					setState(138);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(139);
					_la = _input.LA(1);
					if ( !(_la==ADD || _la==SUB) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(140);
					mulExpr(0);
					}
					} 
				}
				setState(145);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,9,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class MulExprContext extends ParserRuleContext {
		public MulExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_mulExpr; }
	 
		public MulExprContext() { }
		public void copyFrom(MulExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class SingleMulContext extends MulExprContext {
		public UnaryExprContext unaryExpr() {
			return getRuleContext(UnaryExprContext.class,0);
		}
		public SingleMulContext(MulExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class MulMulExprContext extends MulExprContext {
		public MulExprContext mulExpr() {
			return getRuleContext(MulExprContext.class,0);
		}
		public UnaryExprContext unaryExpr() {
			return getRuleContext(UnaryExprContext.class,0);
		}
		public TerminalNode MUL() { return getToken(ToyCParser.MUL, 0); }
		public TerminalNode DIV() { return getToken(ToyCParser.DIV, 0); }
		public TerminalNode MOD() { return getToken(ToyCParser.MOD, 0); }
		public MulMulExprContext(MulExprContext ctx) { copyFrom(ctx); }
	}

	public final MulExprContext mulExpr() throws RecognitionException {
		return mulExpr(0);
	}

	private MulExprContext mulExpr(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		MulExprContext _localctx = new MulExprContext(_ctx, _parentState);
		MulExprContext _prevctx = _localctx;
		int _startState = 20;
		enterRecursionRule(_localctx, 20, RULE_mulExpr, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			_localctx = new SingleMulContext(_localctx);
			_ctx = _localctx;
			_prevctx = _localctx;

			setState(147);
			unaryExpr();
			}
			_ctx.stop = _input.LT(-1);
			setState(154);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new MulMulExprContext(new MulExprContext(_parentctx, _parentState));
					pushNewRecursionContext(_localctx, _startState, RULE_mulExpr);
					setState(149);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(150);
					_la = _input.LA(1);
					if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 3670016L) != 0)) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(151);
					unaryExpr();
					}
					} 
				}
				setState(156);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class UnaryExprContext extends ParserRuleContext {
		public UnaryExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_unaryExpr; }
	 
		public UnaryExprContext() { }
		public void copyFrom(UnaryExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class MulUnaryOpContext extends UnaryExprContext {
		public UnaryExprContext unaryExpr() {
			return getRuleContext(UnaryExprContext.class,0);
		}
		public TerminalNode ADD() { return getToken(ToyCParser.ADD, 0); }
		public TerminalNode SUB() { return getToken(ToyCParser.SUB, 0); }
		public TerminalNode NOT() { return getToken(ToyCParser.NOT, 0); }
		public MulUnaryOpContext(UnaryExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class SingleUnaryContext extends UnaryExprContext {
		public PrimaryExprContext primaryExpr() {
			return getRuleContext(PrimaryExprContext.class,0);
		}
		public SingleUnaryContext(UnaryExprContext ctx) { copyFrom(ctx); }
	}

	public final UnaryExprContext unaryExpr() throws RecognitionException {
		UnaryExprContext _localctx = new UnaryExprContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_unaryExpr);
		int _la;
		try {
			setState(160);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case LPAREN:
			case ID:
			case NUMBER:
				_localctx = new SingleUnaryContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(157);
				primaryExpr();
				}
				break;
			case ADD:
			case SUB:
			case NOT:
				_localctx = new MulUnaryOpContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(158);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 4587520L) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(159);
				unaryExpr();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PrimaryExprContext extends ParserRuleContext {
		public PrimaryExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_primaryExpr; }
	 
		public PrimaryExprContext() { }
		public void copyFrom(PrimaryExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class IdentifierContext extends PrimaryExprContext {
		public TerminalNode ID() { return getToken(ToyCParser.ID, 0); }
		public IdentifierContext(PrimaryExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ParenthesizedExprContext extends PrimaryExprContext {
		public TerminalNode LPAREN() { return getToken(ToyCParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(ToyCParser.RPAREN, 0); }
		public ParenthesizedExprContext(PrimaryExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FunctionCallContext extends PrimaryExprContext {
		public TerminalNode ID() { return getToken(ToyCParser.ID, 0); }
		public TerminalNode LPAREN() { return getToken(ToyCParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(ToyCParser.RPAREN, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(ToyCParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(ToyCParser.COMMA, i);
		}
		public FunctionCallContext(PrimaryExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class NumberLiteralContext extends PrimaryExprContext {
		public TerminalNode NUMBER() { return getToken(ToyCParser.NUMBER, 0); }
		public NumberLiteralContext(PrimaryExprContext ctx) { copyFrom(ctx); }
	}

	public final PrimaryExprContext primaryExpr() throws RecognitionException {
		PrimaryExprContext _localctx = new PrimaryExprContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_primaryExpr);
		int _la;
		try {
			setState(181);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,14,_ctx) ) {
			case 1:
				_localctx = new IdentifierContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(162);
				match(ID);
				}
				break;
			case 2:
				_localctx = new NumberLiteralContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(163);
				match(NUMBER);
				}
				break;
			case 3:
				_localctx = new ParenthesizedExprContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(164);
				match(LPAREN);
				setState(165);
				expr();
				setState(166);
				match(RPAREN);
				}
				break;
			case 4:
				_localctx = new FunctionCallContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(168);
				match(ID);
				setState(169);
				match(LPAREN);
				setState(178);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 3292921856L) != 0)) {
					{
					setState(170);
					expr();
					setState(175);
					_errHandler.sync(this);
					_la = _input.LA(1);
					while (_la==COMMA) {
						{
						{
						setState(171);
						match(COMMA);
						setState(172);
						expr();
						}
						}
						setState(177);
						_errHandler.sync(this);
						_la = _input.LA(1);
					}
					}
				}

				setState(180);
				match(RPAREN);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 6:
			return lOrExpr_sempred((LOrExprContext)_localctx, predIndex);
		case 7:
			return lAndExpr_sempred((LAndExprContext)_localctx, predIndex);
		case 8:
			return relExpr_sempred((RelExprContext)_localctx, predIndex);
		case 9:
			return addExpr_sempred((AddExprContext)_localctx, predIndex);
		case 10:
			return mulExpr_sempred((MulExprContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean lOrExpr_sempred(LOrExprContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean lAndExpr_sempred(LAndExprContext _localctx, int predIndex) {
		switch (predIndex) {
		case 1:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean relExpr_sempred(RelExprContext _localctx, int predIndex) {
		switch (predIndex) {
		case 2:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean addExpr_sempred(AddExprContext _localctx, int predIndex) {
		switch (predIndex) {
		case 3:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean mulExpr_sempred(MulExprContext _localctx, int predIndex) {
		switch (predIndex) {
		case 4:
			return precpred(_ctx, 1);
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u0001\"\u00b8\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0001\u0000\u0004\u0000\u001c\b\u0000\u000b\u0000\f\u0000\u001d"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0005\u0001&\b\u0001\n\u0001\f\u0001)\t\u0001\u0003\u0001+\b\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0001"+
		"\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0003\u0003J\b"+
		"\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0001\u0003\u0001\u0003\u0003\u0003Z\b\u0003\u0001\u0004\u0001"+
		"\u0004\u0005\u0004^\b\u0004\n\u0004\f\u0004a\t\u0004\u0001\u0004\u0001"+
		"\u0004\u0001\u0005\u0001\u0005\u0001\u0006\u0001\u0006\u0001\u0006\u0001"+
		"\u0006\u0001\u0006\u0001\u0006\u0005\u0006m\b\u0006\n\u0006\f\u0006p\t"+
		"\u0006\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001"+
		"\u0007\u0005\u0007x\b\u0007\n\u0007\f\u0007{\t\u0007\u0001\b\u0001\b\u0001"+
		"\b\u0001\b\u0001\b\u0001\b\u0005\b\u0083\b\b\n\b\f\b\u0086\t\b\u0001\t"+
		"\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0005\t\u008e\b\t\n\t\f\t\u0091"+
		"\t\t\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0005\n\u0099\b\n"+
		"\n\n\f\n\u009c\t\n\u0001\u000b\u0001\u000b\u0001\u000b\u0003\u000b\u00a1"+
		"\b\u000b\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001"+
		"\f\u0001\f\u0001\f\u0001\f\u0005\f\u00ae\b\f\n\f\f\f\u00b1\t\f\u0003\f"+
		"\u00b3\b\f\u0001\f\u0003\f\u00b6\b\f\u0001\f\u0000\u0005\f\u000e\u0010"+
		"\u0012\u0014\r\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014\u0016"+
		"\u0018\u0000\u0005\u0001\u0000\u0001\u0002\u0001\u0000\u000b\u0010\u0001"+
		"\u0000\u0011\u0012\u0001\u0000\u0013\u0015\u0002\u0000\u0011\u0012\u0016"+
		"\u0016\u00c3\u0000\u001b\u0001\u0000\u0000\u0000\u0002\u001f\u0001\u0000"+
		"\u0000\u0000\u0004/\u0001\u0000\u0000\u0000\u0006Y\u0001\u0000\u0000\u0000"+
		"\b[\u0001\u0000\u0000\u0000\nd\u0001\u0000\u0000\u0000\ff\u0001\u0000"+
		"\u0000\u0000\u000eq\u0001\u0000\u0000\u0000\u0010|\u0001\u0000\u0000\u0000"+
		"\u0012\u0087\u0001\u0000\u0000\u0000\u0014\u0092\u0001\u0000\u0000\u0000"+
		"\u0016\u00a0\u0001\u0000\u0000\u0000\u0018\u00b5\u0001\u0000\u0000\u0000"+
		"\u001a\u001c\u0003\u0002\u0001\u0000\u001b\u001a\u0001\u0000\u0000\u0000"+
		"\u001c\u001d\u0001\u0000\u0000\u0000\u001d\u001b\u0001\u0000\u0000\u0000"+
		"\u001d\u001e\u0001\u0000\u0000\u0000\u001e\u0001\u0001\u0000\u0000\u0000"+
		"\u001f \u0007\u0000\u0000\u0000 !\u0005\u001e\u0000\u0000!*\u0005\u001a"+
		"\u0000\u0000\"\'\u0003\u0004\u0002\u0000#$\u0005\u0019\u0000\u0000$&\u0003"+
		"\u0004\u0002\u0000%#\u0001\u0000\u0000\u0000&)\u0001\u0000\u0000\u0000"+
		"\'%\u0001\u0000\u0000\u0000\'(\u0001\u0000\u0000\u0000(+\u0001\u0000\u0000"+
		"\u0000)\'\u0001\u0000\u0000\u0000*\"\u0001\u0000\u0000\u0000*+\u0001\u0000"+
		"\u0000\u0000+,\u0001\u0000\u0000\u0000,-\u0005\u001b\u0000\u0000-.\u0003"+
		"\b\u0004\u0000.\u0003\u0001\u0000\u0000\u0000/0\u0005\u0001\u0000\u0000"+
		"01\u0005\u001e\u0000\u00001\u0005\u0001\u0000\u0000\u00002Z\u0003\b\u0004"+
		"\u00003Z\u0005\u0018\u0000\u000045\u0003\n\u0005\u000056\u0005\u0018\u0000"+
		"\u00006Z\u0001\u0000\u0000\u000078\u0005\u001e\u0000\u000089\u0005\u0017"+
		"\u0000\u00009:\u0003\n\u0005\u0000:;\u0005\u0018\u0000\u0000;Z\u0001\u0000"+
		"\u0000\u0000<=\u0005\u0001\u0000\u0000=>\u0005\u001e\u0000\u0000>?\u0005"+
		"\u0017\u0000\u0000?@\u0003\n\u0005\u0000@A\u0005\u0018\u0000\u0000AZ\u0001"+
		"\u0000\u0000\u0000BC\u0005\u0003\u0000\u0000CD\u0005\u001a\u0000\u0000"+
		"DE\u0003\n\u0005\u0000EF\u0005\u001b\u0000\u0000FI\u0003\u0006\u0003\u0000"+
		"GH\u0005\u0004\u0000\u0000HJ\u0003\u0006\u0003\u0000IG\u0001\u0000\u0000"+
		"\u0000IJ\u0001\u0000\u0000\u0000JZ\u0001\u0000\u0000\u0000KL\u0005\u0005"+
		"\u0000\u0000LM\u0005\u001a\u0000\u0000MN\u0003\n\u0005\u0000NO\u0005\u001b"+
		"\u0000\u0000OP\u0003\u0006\u0003\u0000PZ\u0001\u0000\u0000\u0000QR\u0005"+
		"\u0006\u0000\u0000RZ\u0005\u0018\u0000\u0000ST\u0005\u0007\u0000\u0000"+
		"TZ\u0005\u0018\u0000\u0000UV\u0005\b\u0000\u0000VW\u0003\n\u0005\u0000"+
		"WX\u0005\u0018\u0000\u0000XZ\u0001\u0000\u0000\u0000Y2\u0001\u0000\u0000"+
		"\u0000Y3\u0001\u0000\u0000\u0000Y4\u0001\u0000\u0000\u0000Y7\u0001\u0000"+
		"\u0000\u0000Y<\u0001\u0000\u0000\u0000YB\u0001\u0000\u0000\u0000YK\u0001"+
		"\u0000\u0000\u0000YQ\u0001\u0000\u0000\u0000YS\u0001\u0000\u0000\u0000"+
		"YU\u0001\u0000\u0000\u0000Z\u0007\u0001\u0000\u0000\u0000[_\u0005\u001c"+
		"\u0000\u0000\\^\u0003\u0006\u0003\u0000]\\\u0001\u0000\u0000\u0000^a\u0001"+
		"\u0000\u0000\u0000_]\u0001\u0000\u0000\u0000_`\u0001\u0000\u0000\u0000"+
		"`b\u0001\u0000\u0000\u0000a_\u0001\u0000\u0000\u0000bc\u0005\u001d\u0000"+
		"\u0000c\t\u0001\u0000\u0000\u0000de\u0003\f\u0006\u0000e\u000b\u0001\u0000"+
		"\u0000\u0000fg\u0006\u0006\uffff\uffff\u0000gh\u0003\u000e\u0007\u0000"+
		"hn\u0001\u0000\u0000\u0000ij\n\u0001\u0000\u0000jk\u0005\t\u0000\u0000"+
		"km\u0003\u000e\u0007\u0000li\u0001\u0000\u0000\u0000mp\u0001\u0000\u0000"+
		"\u0000nl\u0001\u0000\u0000\u0000no\u0001\u0000\u0000\u0000o\r\u0001\u0000"+
		"\u0000\u0000pn\u0001\u0000\u0000\u0000qr\u0006\u0007\uffff\uffff\u0000"+
		"rs\u0003\u0010\b\u0000sy\u0001\u0000\u0000\u0000tu\n\u0001\u0000\u0000"+
		"uv\u0005\n\u0000\u0000vx\u0003\u0010\b\u0000wt\u0001\u0000\u0000\u0000"+
		"x{\u0001\u0000\u0000\u0000yw\u0001\u0000\u0000\u0000yz\u0001\u0000\u0000"+
		"\u0000z\u000f\u0001\u0000\u0000\u0000{y\u0001\u0000\u0000\u0000|}\u0006"+
		"\b\uffff\uffff\u0000}~\u0003\u0012\t\u0000~\u0084\u0001\u0000\u0000\u0000"+
		"\u007f\u0080\n\u0001\u0000\u0000\u0080\u0081\u0007\u0001\u0000\u0000\u0081"+
		"\u0083\u0003\u0012\t\u0000\u0082\u007f\u0001\u0000\u0000\u0000\u0083\u0086"+
		"\u0001\u0000\u0000\u0000\u0084\u0082\u0001\u0000\u0000\u0000\u0084\u0085"+
		"\u0001\u0000\u0000\u0000\u0085\u0011\u0001\u0000\u0000\u0000\u0086\u0084"+
		"\u0001\u0000\u0000\u0000\u0087\u0088\u0006\t\uffff\uffff\u0000\u0088\u0089"+
		"\u0003\u0014\n\u0000\u0089\u008f\u0001\u0000\u0000\u0000\u008a\u008b\n"+
		"\u0001\u0000\u0000\u008b\u008c\u0007\u0002\u0000\u0000\u008c\u008e\u0003"+
		"\u0014\n\u0000\u008d\u008a\u0001\u0000\u0000\u0000\u008e\u0091\u0001\u0000"+
		"\u0000\u0000\u008f\u008d\u0001\u0000\u0000\u0000\u008f\u0090\u0001\u0000"+
		"\u0000\u0000\u0090\u0013\u0001\u0000\u0000\u0000\u0091\u008f\u0001\u0000"+
		"\u0000\u0000\u0092\u0093\u0006\n\uffff\uffff\u0000\u0093\u0094\u0003\u0016"+
		"\u000b\u0000\u0094\u009a\u0001\u0000\u0000\u0000\u0095\u0096\n\u0001\u0000"+
		"\u0000\u0096\u0097\u0007\u0003\u0000\u0000\u0097\u0099\u0003\u0016\u000b"+
		"\u0000\u0098\u0095\u0001\u0000\u0000\u0000\u0099\u009c\u0001\u0000\u0000"+
		"\u0000\u009a\u0098\u0001\u0000\u0000\u0000\u009a\u009b\u0001\u0000\u0000"+
		"\u0000\u009b\u0015\u0001\u0000\u0000\u0000\u009c\u009a\u0001\u0000\u0000"+
		"\u0000\u009d\u00a1\u0003\u0018\f\u0000\u009e\u009f\u0007\u0004\u0000\u0000"+
		"\u009f\u00a1\u0003\u0016\u000b\u0000\u00a0\u009d\u0001\u0000\u0000\u0000"+
		"\u00a0\u009e\u0001\u0000\u0000\u0000\u00a1\u0017\u0001\u0000\u0000\u0000"+
		"\u00a2\u00b6\u0005\u001e\u0000\u0000\u00a3\u00b6\u0005\u001f\u0000\u0000"+
		"\u00a4\u00a5\u0005\u001a\u0000\u0000\u00a5\u00a6\u0003\n\u0005\u0000\u00a6"+
		"\u00a7\u0005\u001b\u0000\u0000\u00a7\u00b6\u0001\u0000\u0000\u0000\u00a8"+
		"\u00a9\u0005\u001e\u0000\u0000\u00a9\u00b2\u0005\u001a\u0000\u0000\u00aa"+
		"\u00af\u0003\n\u0005\u0000\u00ab\u00ac\u0005\u0019\u0000\u0000\u00ac\u00ae"+
		"\u0003\n\u0005\u0000\u00ad\u00ab\u0001\u0000\u0000\u0000\u00ae\u00b1\u0001"+
		"\u0000\u0000\u0000\u00af\u00ad\u0001\u0000\u0000\u0000\u00af\u00b0\u0001"+
		"\u0000\u0000\u0000\u00b0\u00b3\u0001\u0000\u0000\u0000\u00b1\u00af\u0001"+
		"\u0000\u0000\u0000\u00b2\u00aa\u0001\u0000\u0000\u0000\u00b2\u00b3\u0001"+
		"\u0000\u0000\u0000\u00b3\u00b4\u0001\u0000\u0000\u0000\u00b4\u00b6\u0005"+
		"\u001b\u0000\u0000\u00b5\u00a2\u0001\u0000\u0000\u0000\u00b5\u00a3\u0001"+
		"\u0000\u0000\u0000\u00b5\u00a4\u0001\u0000\u0000\u0000\u00b5\u00a8\u0001"+
		"\u0000\u0000\u0000\u00b6\u0019\u0001\u0000\u0000\u0000\u000f\u001d\'*"+
		"IY_ny\u0084\u008f\u009a\u00a0\u00af\u00b2\u00b5";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}